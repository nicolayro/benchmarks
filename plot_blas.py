import matplotlib.pyplot as plt
import numpy as np
import os

PATH = "results/blas/idun"

x = []
y = []
e = []
files = os.listdir(PATH)

for filename in files:
    data = []
    with open(f'{PATH}/{filename}') as file:
        n = file.readline().split("=")[-1].strip()
        if not n.isdecimal():
            print(f"ERROR: Format error in file {filename}")
            continue

        for idx, line in enumerate(file):
            num = line.split(" ")[0]
            if num[0].isdecimal():
                data.append(float(num))

    if len(data) == 0:
        print(f"ERROR: No data found for file {filename}")
        continue
    extimes = np.array(data)

    x.append(int(n))
    y.append(np.mean(extimes))
    e.append(np.std(extimes))

order = np.argsort(x)
x = np.array(x)[order]
y = np.array(y)[order]

fig, ax = plt.subplots()
# ax.plot(x, y)
ax.errorbar(x, y, e, fmt='-o', capsize=3)
plt.xlabel('N')
plt.ylabel('Gflops/s')

plt.savefig("test.png", dpi=300)

plt.show()
