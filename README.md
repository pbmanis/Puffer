# Puffer
Arduino sketch for "puffer pipette" controller

This short sketch is for a controller for a puffer pipette for injection of dyes into tissue. The controller is part of a system that includes
a 12V 1A power supply, an IRF511-based driver that takes a TTL input and opens the valve, a General Valve 3-way valve (NO/NC ports), and a pressure regulator that goes down to a few PSI. We provide the air pressure from the house nitrogen. 

The controller requires:
  1. A pushbutton switch connected to ground on Pin 9
  2. A potentiometer, between 3.3V and ground, with the wiper connected to A0. (10K would be good; too high and you loose range as the A-D input requires a good bit of current to get a reading). 
  3. The output to the IRF511 input comes from Pin 12

The potentiometer contols the duration of the valve opening. In the current version, only a few values over the range 10-500 msec are interpreted. There is a debounce on the trigger switch, and a refractory period of 0.5 seconds built into the code. 

1/26/2017 pbm
