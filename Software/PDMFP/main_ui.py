import sys
import serial
import struct
import csv
from collections import deque
from PyQt5.QtWidgets import (QApplication, QWidget, QVBoxLayout, QHBoxLayout,
                             QLabel, QLineEdit, QPushButton, QGroupBox, QFormLayout, QFileDialog)
from PyQt5.QtCore import QTimer
import pyqtgraph as pg

# --- Configuration ---
SERIAL_PORT = 'COM3'  # Update with your active port
BAUD_RATE = 115200    
MAX_POINTS = 500      

# --- Struct Formats (Mapped to SharedData.h) ---
# '<' = Little-endian. 'f' = float (4 bytes). 'B' = uint8_t (1 byte). 'x' = pad byte.
# NOTE on CTRL_PARAMS_FMT: 32-bit microcontrollers (ESP32, Teensy, ARM) automatically pad 
# structs to 4-byte boundaries. 'BB' is 2 bytes, so '2x' adds 2 bytes of blank padding 
# before the floats. If using an 8-bit Arduino (Uno/Mega), remove the '2x' -> '<BB3f'
SYSTEM_STATE_FMT = '<8f'       # 8 floats: clock, Q, Q_targ, P, P_targ, DC1, DC2, Vol
SYSTEM_STATE_SIZE = struct.calcsize(SYSTEM_STATE_FMT)

CTRL_PARAMS_FMT = '<BB2x3f'    # 2 uint8_t, 2 pad bytes, 3 floats
PID_GAINS_FMT = '<9f'          # 9 floats

class MicrofluidicUI(QWidget):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Microfluidic Pump Control")
        self.resize(1200, 800)

        # 1. Recording State
        self.is_recording = False
        self.csv_file = None
        self.csv_writer = None
        
        # 2. Plot Data Buffers
        self.clock_data = deque(maxlen=MAX_POINTS)
        self.p_data = deque(maxlen=MAX_POINTS)
        self.p_target_data = deque(maxlen=MAX_POINTS)
        self.q_data = deque(maxlen=MAX_POINTS)
        self.q_target_data = deque(maxlen=MAX_POINTS)
        self.dc1_data = deque(maxlen=MAX_POINTS)
        self.dc2_data = deque(maxlen=MAX_POINTS)

        # 3. Serial Setup
        try:
            self.ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=0.05)
        except serial.SerialException:
            print(f"Warning: Could not open {SERIAL_PORT}.")
            self.ser = None

        self.init_ui()

        # 4. Timer for Polling Serial
        self.timer = QTimer()
        self.timer.timeout.connect(self.update_data)
        self.timer.start(50)

    def init_ui(self):
        main_layout = QHBoxLayout()

        # ================= LEFT PANEL: PLOTS =================
        plot_layout = QVBoxLayout()
        pg.setConfigOptions(antialias=True) 

        # Pressure Plot
        self.plot_p = pg.PlotWidget(title="Pressure (P vs P_target)")
        self.plot_p.addLegend()
        self.plot_p.showGrid(x=True, y=True)
        self.line_p = self.plot_p.plot(pen='y', name='P')
        self.line_p_target = self.plot_p.plot(pen='r', name='P_target')
        plot_layout.addWidget(self.plot_p)

        # Flow Rate Plot
        self.plot_q = pg.PlotWidget(title="Flow Rate (Q vs Q_target)")
        self.plot_q.addLegend()
        self.plot_q.showGrid(x=True, y=True)
        self.line_q = self.plot_q.plot(pen='c', name='Q')
        self.line_q_target = self.plot_q.plot(pen='r', name='Q_target')
        plot_layout.addWidget(self.plot_q)

        # Duty Cycle Plot
        self.plot_dc = pg.PlotWidget(title="Duty Cycles (DC1 & DC2)")
        self.plot_dc.addLegend()
        self.plot_dc.showGrid(x=True, y=True)
        self.line_dc1 = self.plot_dc.plot(pen='g', name='DC1')
        self.line_dc2 = self.plot_dc.plot(pen='m', name='DC2')
        plot_layout.addWidget(self.plot_dc)

        main_layout.addLayout(plot_layout, stretch=3) 

        # ================= RIGHT PANEL: INPUTS =================
        input_layout = QVBoxLayout()
        
        # Record Button
        self.record_btn = QPushButton("Start Recording CSV")
        self.record_btn.setStyleSheet("background-color: lightgreen;")
        self.record_btn.clicked.connect(self.toggle_recording)
        input_layout.addWidget(self.record_btn)

        # -- Control Params Group --
        ctrl_group = QGroupBox("Control Parameters")
        ctrl_form = QFormLayout()
        self.ctrl_inputs = {}
        ctrl_labels = ['selection (uint8)', 'type (uint8)', 'param_1 (float)', 'param_2 (float)', 'param_3 (float)']
        
        for label in ctrl_labels:
            line_edit = QLineEdit("0") # Default to 0
            self.ctrl_inputs[label] = line_edit
            ctrl_form.addRow(QLabel(label), line_edit)

        self.send_ctrl_btn = QPushButton("Send Control Params")
        self.send_ctrl_btn.clicked.connect(self.send_control_params)
        ctrl_form.addWidget(self.send_ctrl_btn)
        ctrl_group.setLayout(ctrl_form)
        input_layout.addWidget(ctrl_group)

        # -- PID Gains Group --
        pid_group = QGroupBox("PID Gains")
        pid_form = QFormLayout()
        self.pid_inputs = {}
        pid_labels = ['P_FR', 'I_FR', 'D_FR', 'P_V1', 'I_V1', 'D_V1', 'P_V2', 'I_V2', 'D_V2']
        
        for label in pid_labels:
            line_edit = QLineEdit("0.0") 
            self.pid_inputs[label] = line_edit
            pid_form.addRow(QLabel(label), line_edit)

        self.send_pid_btn = QPushButton("Send PID Gains")
        self.send_pid_btn.clicked.connect(self.send_pid_gains)
        pid_form.addWidget(self.send_pid_btn)
        pid_group.setLayout(pid_form)
        input_layout.addWidget(pid_group)

        input_layout.addStretch() 
        main_layout.addLayout(input_layout, stretch=1) 
        self.setLayout(main_layout)

    # ================= DATA HANDLING =================
    def update_data(self):
        """Reads systemState struct from Serial and updates UI/CSV."""
        if not self.ser: return

        while self.ser.in_waiting >= SYSTEM_STATE_SIZE:
            try:
                raw_bytes = self.ser.read(SYSTEM_STATE_SIZE)
                
                # Unpack matches systemState order in SharedData.h
                clock, q, q_targ, p, p_targ, dc1, dc2, vol = struct.unpack(SYSTEM_STATE_FMT, raw_bytes)

                # Append to deques
                self.clock_data.append(clock)
                self.p_data.append(p)
                self.p_target_data.append(p_targ)
                self.q_data.append(q)
                self.q_target_data.append(q_targ)
                self.dc1_data.append(dc1)
                self.dc2_data.append(dc2)

                # Update plots
                self.line_p.setData(self.clock_data, self.p_data)
                self.line_p_target.setData(self.clock_data, self.p_target_data)
                self.line_q.setData(self.clock_data, self.q_data)
                self.line_q_target.setData(self.clock_data, self.q_target_data)
                self.line_dc1.setData(self.clock_data, self.dc1_data)
                self.line_dc2.setData(self.clock_data, self.dc2_data)

                # Log to CSV
                if self.is_recording and self.csv_writer:
                    self.csv_writer.writerow([clock, q, q_targ, p, p_targ, dc1, dc2, vol])

            except struct.error:
                self.ser.flushInput() 

    # ================= SENDING COMMANDS =================
    def send_control_params(self):
        """Packs controlParams and sends with 0x01 message type."""
        if not self.ser: return
        try:
            # Extract inputs
            sel = int(self.ctrl_inputs['selection (uint8)'].text())
            typ = int(self.ctrl_inputs['type (uint8)'].text())
            p1 = float(self.ctrl_inputs['param_1 (float)'].text())
            p2 = float(self.ctrl_inputs['param_2 (float)'].text())
            p3 = float(self.ctrl_inputs['param_3 (float)'].text())

            # Pack byte 0x01, then the struct
            msg = struct.pack('<B', 0x01) + struct.pack(CTRL_PARAMS_FMT, sel, typ, p1, p2, p3)
            self.ser.write(msg)
            print("Sent Control Params")
        except ValueError:
            print("Invalid input: Ensure ints for selection/type, floats for params.")

    def send_pid_gains(self):
        """Packs pidGains and sends with 0x02 message type."""
        if not self.ser: return
        try:
            # Extract all 9 floats sequentially
            gains = [float(self.pid_inputs[lbl].text()) for lbl in self.pid_inputs]

            # Pack byte 0x02, then the struct
            msg = struct.pack('<B', 0x02) + struct.pack(PID_GAINS_FMT, *gains)
            self.ser.write(msg)
            print("Sent PID Gains")
        except ValueError:
            print("Invalid input: Ensure all PID gains are floats.")

    # ================= RECORDING =================
    def toggle_recording(self):
        """Starts/Stops CSV streaming."""
        if not self.is_recording:
            opts = QFileDialog.Options()
            filepath, _ = QFileDialog.getSaveFileName(self, "Save Data As", "", "CSV Files (*.csv)", options=opts)
            if filepath:
                self.csv_file = open(filepath, mode='w', newline='')
                self.csv_writer = csv.writer(self.csv_file)
                self.csv_writer.writerow(['Clock', 'Q', 'Q_target', 'P', 'P_target', 'DC1', 'DC2', 'Volume'])
                
                self.is_recording = True
                self.record_btn.setText("Stop Recording")
                self.record_btn.setStyleSheet("background-color: lightcoral;")
        else:
            self.is_recording = False
            self.record_btn.setText("Start Recording CSV")
            self.record_btn.setStyleSheet("background-color: lightgreen;")
            if self.csv_file:
                self.csv_file.close()
                self.csv_file = None
                self.csv_writer = None

if __name__ == '__main__':
    app = QApplication(sys.argv)
    window = MicrofluidicUI()
    window.show()
    sys.exit(app.exec_())