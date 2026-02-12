import serial
import numpy as np
import matplotlib.pyplot as plt
import time
from serial.tools import list_ports

def read_serial():
    port = '/dev/cu.usbmodem1101'
    data = []
    
    # Open serial connection
    ser = serial.Serial(port, baudrate=9600, timeout=1.0)
    
    try:
        while True:
            # Read and decode line
            if value := ser.readline().decode().strip():
                number = float(value)
                data.append(number)
                print(number)
    except KeyboardInterrupt:
        ser.close()
        return np.array(data)

start_time = time.time()
data_matrix = read_serial()
end_time = time.time()
duration = end_time - start_time

np.savetxt("frs_calib_test4.csv", data_matrix, delimiter=",")

x = np.linspace(0, duration, len(data_matrix))
print("Duration: ", duration)
print("Length of data: ", len(data_matrix))
plt.plot(x, data_matrix)
plt.ylabel("Flow rate (uL/min)")
plt.xlabel("Time (s)")
plt.grid()
plt.show()