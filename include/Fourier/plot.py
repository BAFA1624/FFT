import csv
import numpy as np
import matplotlib.pyplot as plt


times1, real1, imag1 = [], [], []
times2, real2, imag2 = [], [], []

with open("../../results.txt", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        times1.append(np.float64(row['time']))
        real1.append(np.float64(row['real']))
        imag1.append(np.float64(row['imag']))
with open("../../h.txt", "r") as file:
    reader = csv.DictReader(file)
    for row in reader:
        times2.append(np.float64(row['time']))
        real2.append(np.float64(row['real']))
        imag2.append(np.float64(row['imag']))

fig, axs = plt.subplots(2, 1,
                        figsize=(10, 10))

axs[0].plot(times1, real1, label="original real")
axs[0].plot(times1, imag1, label="original imag")
axs[0].plot(times2, real2, label="transformed real")
axs[0].plot(times2, imag2, label="transformed imag")
# axs[0].set_title("Original function")

axs[0].legend()

axs[1].plot(times1, real1, label="real")
axs[1].plot(times1, imag1, label="imag")
axs[1].set_title("ifft(DFT results)")

axs[1].legend()

plt.show()
