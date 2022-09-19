import time
from serial import Serial
import numpy as np
import matplotlib.pyplot as plt
ArduinoSerial = Serial('COM3', 38400)
print(ArduinoSerial)
collect_time = 1
ArduinoSerial.write(b's')
start = time.perf_counter()
t = start
i = 0
#print ('initially:',t-start)
times = []
angles = []
mystrings = []

while ((ArduinoSerial.in_waiting > 0) or (t-start < collect_time)):
    print("1")
    print(ArduinoSerial.readline())
    c = ArduinoSerial.readline()[:-2]
    print("1.5")
    # print(c)
    a, ti = np.fromstring(c, count=2, sep=',')
#    print(a,ti)
    print("2")
    times = np.append(times, ti*1e-6)
    angles = np.append(angles, a)
#    time.sleep(.02)
    t = time.perf_counter()
    print(t)
#    print(t-start)

ArduinoSerial.write(b'q')
i = 1
ArduinoSerial.close()
ArduinoSerial.close()  # check everything is closed
plt.plot(times, angles)
plt.show()
np.savetxt('testdata1.csv', np.transpose([times, angles]), delimiter=',')
