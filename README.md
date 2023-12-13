# secd

A near-minimal implementation in C of P. J. Landin's 1964 virtual machine. 

https://en.wikipedia.org/wiki/SECD_machine

The barest minimum of Lisp is also implemented to support the machine's execution.

## The machine
The machine uses four integer registers, S (Stack), E (Environment), C (Control), and D (Dump), and a 256-integer memory. The 32 lowest memory locations hold small integers in the range 0, 1, 2, ..., 31. The following 32 memory locations hold other integers as they occur in a script. The cells from 64 and up are used to store cons pairs, with the lowest 8 bits being the cdr and the next 8 bits being the car. That is, the values aren't tagged: instead their location in memory shows their type. The value 0, in the cell #0, stands for both zero and the empty list (it is breakable but mostly works).

The machine can be run using a script in a file, which it executes and then exits, or in a "repl" mode, where the user can input a script piecemeal: the machine executes as many operations as it has been given and then keeps its state waiting for further input. Exit the loop with CTRL-D. Scripts (or script fragments) must be written as Lisp lists within parentheses or square brackets. Symbols can be written in either case: they are read as uppercase.

The basic operations are supported, as well as NIL and T, and some more comparison operators (GT, LT, GEQ), and a couple of utility operations like SWAP (swaps the two values on the top of the stack), UNCONS (splits a cons into two values on the top of the stack) and DUP (duplicates the top value on the stack). A small script repository is in the directory `scripts`. The scripts are rudimentary and mostly pointless other than as an illustration of execution.

## Lisp support
To support the machine, the following Lisp functions have been implemented: cons, car, cdr, rplaca (setf (car ...) ...), rplacd (setf (cdr ...) ...) (not actually used, but included for symmetry), print(value), print(pair), read(value), and read(pair).
