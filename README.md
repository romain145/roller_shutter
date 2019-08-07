Code for a simple Roller Shutter.
The control board has an RF receiver and a pulse signal input. It has 2 relays and operates a 3-wire roller shutter (1 is Neutral, 1 for UP, 1 for DOWN).
The board is powered by a 16F648A.

The roller shutter only operates like this on the pulse input: DOWN - STOP - UP - STOP.
It is impossible to configure the board for a dead-man switch (move on press, stop on release).

So this quick and dirty firmware does that, by throwing away the RF feature of the board (would need to implement reading the code sent from a remote control, handle programming etc...). The pulse input was enough for me. Feel free to fork, reuse, modify etc...
