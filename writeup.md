# Udacity Self Driving Car Engineer Nanodegree Project 8: PID Control

---

## Motivation
The purpose of this project is to design a PID controller for steering control in a vehicle simulator driving around a testing track. PID controllers are used widely in industry as a basic linear control theory technique, when more complicated methods such as MPC (Model Predictive Control) are not necessary or available. A distinct advantage over PID controllers, compared to other linear time-invariant controllers, is that they can often be tuned without a model of the dynamical system they are being designed to control. If a system is sufficiently linear, PID controllers can behave similarly with regards to how to handle issues such as overshoot and delays.

---

## How PID Controllers Work
A PID controller calculates the control based on three different operations on the incoming error signal: proportional scaling (P), integration (I), and differentiation (D). The output of a PID controller, like any controller in a control system, is a control signal. In this project, the control signal outputted by the PID controller is a steering command to steer the vehicle.

At a minimum, proportional control is needed to drive error to zero. Integral and derivative control are not necessarily required. The inclusion of integral and derivative control in a PID controller both have advantages and drawbacks, and they both serve different purposes.

### Benefits and Drawbacks of Integral Control

The purpose of integral control is usually to reduce steady-state error after proportional and/or derivative control have been applied to the extent possible. The reason that integral control works for this is that in steady-state, the derivative of the error is zero, and the proportional error does not contribute enough to drive the error closer to zero. In contrast, the integral component of the PID control grows over time with a steady-state error, which should drive the error closer to zero over time.

From my personal experience, the main issue with integral control is integral windup. Integral windup occurs when the integrated error grows too large, which causes the integral component of the control to dominate the proportional and derivative terms. This can be remedied by only integrating the error if it is within a threshold, but this introduces another tuning parameter to the control design.

### Benefits and Drawbacks of Derivative Control

The purpose of derivative control is usually to improve the response of proportional and/or integral control. Derivative control can often help with reducing overshooting and oscillation by further reducing the control command as the error decreases than proportional control does on its own.

The main issue with derivative control is that high frequency components of the error signal get amplified by differentiation. If the error signal is noisy, a low pass filter can be used to smoothen it during differentiation. However, this introduces another tuning parameter, the low pass filter time constant. It also introduces an artificial delay in the error, which may adversely affect the quality of the control.

---

## Methodology for Manual PID Controller Tuning Without a System Model

In tuning a PID controller in practice, I generally prefer to avoid integral control if I can, as I find that there are too many additional tuning parameters to decide on to prevent integral windup. I also prefer to see how the controller performs with proportional control alone. If the system performs "well enough," I tend not to add derivative control either, so I can avoid issues with the amplification and low pass filtering of high frequency noise in the error signal. If proportional control is not sufficient (i.e. the system under control is excessively overshooting and/or oscillating), then I introduce derivative control to see if I can improve the response. If the proportional and derivative control work well enough, and steady-state error is not an issue, then I avoid use of the integral term entirely. I only use integral control if steady-state error is problematic.

Note that if a linear time-invariant system model is available, more sophisticated techniques could be used to design a PID controller, such as loop shaping.

---

## Application of Tuning Methodology

In this project, I followed the manual tuning methodology I described above. With even small proportional control gains, the system experienced large oscillations, even during straight line motion. After the first turn of the course, the vehicle became stuck in the water. Thus, I quickly decided that derivative control would be needed to reduce the overshooting and oscillation after turns. I added a small amount of derivative control and the response improved drastically, as I had expected. The vehicle was able to make turns without nearly as much oscillation or overshoot compared to with proportional control alone. I did not need to low pass filter the differentiated error. I iterated by increasing the derivative gain until the performance of the controller was sufficient.

After observing that the steady-state error was negligible after completing a series of turns around the track, I decided not to use integral control.

To speed up the manual tuning process, I created a file called [`gains.txt`](./gains.txt), which contains the P, I, and D gains on lines 1, 2, and 3, respectively. In [`main.cpp`](./src/main.cpp), these gain values are read and used to initialize the PID controller class. This prevented the need to recompile just to change the PID gains.

---

## Results

The final PID gains I chose are as follows:

| Gain | Value |
| :--: | :---: |
|  P   |  0.3  |
|  I   |   0   |
|  D   | 15.0  |

A video of the vehicle being controlled by the PID controller for one lap around the simulator course can be found [here](./P8_video.mov).