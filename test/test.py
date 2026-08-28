from pyfc.pid import AutoOptimizingPID

from matplotlib.animation import FuncAnimation
from matplotlib import pyplot as plt

import numpy as np

setpoint = 1.0

pid = AutoOptimizingPID(setpoint=setpoint, lr=1.0)
pid.init()

z = [0.0]
t = [0.0]
dt = 1e-3

fig, ax = plt.subplots()  
line = ax.plot(t, z)[0]
        
def func(frame):
    global setpoint
    if (frame % 500) == 0:
        if setpoint == 1.0:
            setpoint = 2.0
        elif setpoint == 2.0:
            setpoint = 1.5
        elif setpoint == 1.5:
            setpoint = 2.5
        elif setpoint == 2.5:
            setpoint = 1.0
                
    pid.setSetpoint(setpoint)        
    
    pid_out = pid.requestLoop(z[frame-1])
    
    z.append(z[frame-1] + dt * pid_out)
    t.append(t[frame-1] + dt)

    line.set_xdata(t)
    line.set_ydata(z)
    ax.set_ylim(-0.1, 1.2*np.max(z))
    ax.set_xlim(0, 1.2*np.max(t))
    
anim = FuncAnimation(fig, func, frames=10000, interval=1)
plt.grid()
plt.show()