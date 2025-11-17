import serial
from serial.tools import list_ports

def read_serial():
    port = 'COM3'
    
    # Open serial connection
    ser = serial.Serial(port, baudrate=115200, timeout=1.0)
    
    try:
        while True:
            # Read and decode line
            if line := ser.readline().decode().strip():
                print("Received:", line)
    except KeyboardInterrupt:
        ser.close()

read_serial()