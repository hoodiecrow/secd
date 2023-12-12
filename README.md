# secd

A near-minimal implementation in C of P. J. Landin's 1964 virtual machine. 

https://en.wikipedia.org/wiki/SECD_machine

The barest minimum of Lisp is also implemented to support the machine's execution.

The machine uses four integer registers, S, E, C, and D, and a 256-integer memory. The 32 lowest memory locations hold small integers in the range 0, 1, 2, ..., 31. The following 32 memory locations hold other integers. The cells from 64 and up are used to store cons pairs, with the lowest 8 bits being the cdr and the next 8 bits being the car.
