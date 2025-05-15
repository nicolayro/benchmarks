import matplotlib.pyplot as plt
import numpy as np
import os

lups = 6000*4000*100

def read_data(files):
    x = []
    y = []
    for filename in files:
        data = []
        with open(f'{path}/{filename}') as file:
            threads = filename.split(".")[0].strip()

            total = []
            for line in file:
                elapsed, collide, exchange, stream = line.strip().split()
                total.append(float(collide) + float(stream))
            try:
                avg = sum(total)/len(total)
                y.append(lups/avg)
            except ValueError:
                print(time)
                print(f'ERROR: Format error in file {filename}:')
                print(f'       {data} is not a number')
                y.append(0.0)

        x.append(int(threads))

    order = np.argsort(x)
    x = np.array(x)[order]
    y = np.array(y)[order]

    return x, y


fig, ax = plt.subplots()

path = "compact/double"
files = os.listdir(path)
x, y = read_data(files)

print(y)

ax.plot(x, y)

path = "scatter/double"
files = os.listdir(path)
x, y = read_data(files)
print(y)
ax.plot(x, y)

ax.legend(["compact", "scatter"])
plt.xlabel('# of threads')
plt.ylabel('LUPS')

plt.savefig('d2q7.png', dpi=300)

plt.show()
