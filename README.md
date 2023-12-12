# secd

A near-minimal implementation in C of P. J. Landin's 1964 virtual machine. 

https://en.wikipedia.org/wiki/SECD_machine

The barest minimum of Lisp is also implemented to support the machine's execution.

The machine uses four integer registers, S, E, C, and D, and a 256-integer memory. The 32 lowest memory locations hold small integers in the range 0, 1, 2, ..., 31. The following 32 memory locations hold other integers as they occur in a script. The cells from 64 and up are used to store cons pairs, with the lowest 8 bits being the cdr and the next 8 bits being the car.

The machine can be run using a script in a file, which it executes and then exits, or in a "repl" mode, where the user can input a script peacemeal: the machine executes as many operations as it has been given and then keeps its state waiting for further input. Exit the loop with CTRL-D.
