import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import MaxNLocator

data_matrix = np.loadtxt("frs_calib_test3.csv")

# test 1: duration 1025.5775558948517 length 12983
# test 2: duration 969.6334116458893 length 12267
# test 3: duration 972.1644570827484 length 12299
duration = 972.1644570827484
length = 12299

#for i in range(len(data_matrix)):
 #   if data_matrix[i] >= 200:
#        data_matrix[i] = 0

xdiv = duration / 50
x = np.linspace(0, duration, length)

plt.plot(x, data_matrix)
plt.title("Flow rate sensor calibration results")
plt.ylabel("Flow rate (uL/min)")
plt.xlabel("Time (s)")
plt.ylim(0, 80)
plt.xlim(0,duration)
plt.grid()
ax = plt.gca()  # get current axis
ax.xaxis.set_major_locator(MaxNLocator(nbins=xdiv))
ax.ticklabel_format(useOffset=False)
ax.yaxis.set_major_locator(MaxNLocator(nbins=16))

plt.show()