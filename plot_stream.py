import matplotlib.pyplot as plt
import numpy as np
import os


def read_data(files):
    x = []
    y = []
    e = []
    for filename in files:
        data = []
        with open(f'{path}/{filename}') as file:
            n = file.readline().split("=")[-1].strip()
            _ = file.readline()
            # threads = file.readline().split("=")[-1].strip()
            # Remove headers and first result
            file.readline()
            file.readline()
            threads = filename.split(".")[0].strip()

            if not n.isdecimal() and not threads.isdecimal():
                print(f"ERROR: Format error in file {filename}:")
                print(f"       {n} or {threads} is not decimal")
                continue

            for idx, line in enumerate(file):
                bandwidths = line.split()
                data.append(float(bandwidths[0]))

        if len(data) < 99:
            print(f"ERROR: No data found for file {filename}")
            continue
        times = np.array(data)

        x.append(int(threads))
        y.append(len(times)/np.sum(1.0/times))
        e.append(np.std(times))

    order = np.argsort(x)
    x = np.array(x)[order]
    y = np.array(y)[order]
    e = np.array(e)[order]
    print(y)

    return x, y, e


fig, ax = plt.subplots()

path = "output/compact"
files = os.listdir(path)
x, y, e = read_data(files)

ax.errorbar(x, y, e)

path = "output/scatter"
files = os.listdir(path)
x, y, e = read_data(files)

ax.errorbar(x, y, e)

ax.legend(["compact", "scatter"])
plt.xlabel('# of threads')
plt.ylabel('GB/s')

plt.savefig('stream.png', dpi=300)

plt.show()
