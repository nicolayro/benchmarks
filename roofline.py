import matplotlib.pyplot as plt
import numpy as np

bandwidth = 277.8  # gbyte/s
gflops = 51.062  # gflops
# flops/byte
# -> bandwidth * operational intensity = gflops

break_point = gflops/bandwidth

print(f'{break_point}')
x1, y1 = [1/8, break_point], [1/8*bandwidth, gflops]
x2, y2 = [break_point, 4*break_point], [gflops, gflops]

fig, ax = plt.subplots()
ax.plot(x1, y1, x2, y2, color='tab:blue')

plt.xlabel('Operational intensity (FLOPS/byte)')
plt.ylabel('Floating-point performance (GFLOPS)')

ax.set_xscale('log', base=2)
plt.ylim(top=60)
plt.savefig('roofline.png', dpi=300)
plt.title("Roofline")
plt.show()
