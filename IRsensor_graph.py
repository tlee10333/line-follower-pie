import matplotlib.pyplot as plt
import numpy as np

base_speed = 30
thresholdl = 800
thresholdr = 800
points = []
leftsense = []
leftspeed = []
rightsense = []
rightspeed = []

with open("data.txt", "r") as file:
    for line in file.readlines():
        points.append([int(x) for x in line.split("\n")[0].split(",")])

count = [i for i in range(len(points))]
for point in points:
    if (point[0] < thresholdl) and (point[1] < thresholdr):
        leftsense.append(point[0])
        leftspeed.append(base_speed)
        rightsense.append(point[1])
        rightspeed.append(base_speed)
    elif (point[0] < thresholdl) and (point[1] > thresholdr):
        leftsense.append(point[0])
        leftspeed.append(base_speed)
        rightsense.append(point[1])
        rightspeed.append(0)

    elif (point[0] > thresholdl) and (point[1] < thresholdr):
        leftsense.append(point[0])
        leftspeed.append(0)
        rightsense.append(point[1])
        rightspeed.append(base_speed)
    else:
        leftsense.append(point[0])
        leftspeed.append(0)
        rightsense.append(point[1])
        rightspeed.append(0)


fig, ax = plt.subplots()

# ax.plot(count, leftsense, color="r", label="Left Sensor Data")
ax.plot(count, rightsense, color="r", label="Right Sensor Data")

ax.set_ylabel("Sensor Value", color="r", fontsize=16)

ax2 = ax.twinx()
# ax2.plot(count, leftspeed, color="b", linestyle="dotted", label="Left Motor Speed")
ax2.plot(count, rightspeed, color="b", linestyle="dotted", label="Right Motor Speed")

ax2.set_ylabel("Motor Speed", color="b", fontsize=16)
ax.set_xlabel("Time")

ax.set_title("Superimposed Right Motor & IR Sensor Data During Trial Run")

plt.show()
