#!/usr/bin/env python
import os, sys

base = os.path.dirname(__file__)
path = os.path.dirname(base)
path = os.path.dirname(path)
sys.path.insert(0, path)
try:
    import numpy as np
    import matplotlib.pyplot as plt
except Exception as e:
    print(e)
    exit()

import liba  # type: ignore

traj = liba.trajbell()
traj.gen(3, 2, 3, 0, 10)
data = np.arange(0, traj.t, traj.t / 1000)

plt.figure("bell-shaped velocity trajectory")

plt.subplot(411)
plt.title("bell-shaped velocity trajectory")
plt.ylabel("Position")
plt.plot(data, traj.pos(data), "r-", label="q")
plt.legend()

plt.subplot(412)
plt.ylabel("Velocity")
plt.plot(data, traj.vel(data), "b-", label="v")
plt.legend()

plt.subplot(413)
plt.ylabel("Acceleration")
plt.plot(data, traj.acc(data), "g-", label="a")
plt.legend()

plt.subplot(414)
plt.ylabel("Jerk")
plt.plot(data, traj.jer(data), "k-", label="j")
plt.legend()

plt.xlabel("t")
plt.savefig(os.path.join(base, "bell-shaped_trajectory.png"))
plt.show()
