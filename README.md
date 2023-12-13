# secd

A near-minimal implementation in C of P. J. Landin's 1964 abstract virtual machine. 

https://en.wikipedia.org/wiki/SECD_machine

The barest minimum of Lisp is also implemented to support the machine's execution.

## The machine
The machine uses four 8-bit integer registers, S (Stack), E (Environment), C (Control), and D (Dump), and a 256x16-bit-integer memory. The 32 lowest memory locations hold small integers in the range 0, 1, 2, ..., 31. The following 32 memory locations hold other integers as they occur in a script. The cells from 64 and up are used to store cons pairs, with the lowest 8 bits being the cdr and the next 8 bits being the car. That is, the values aren't tagged: instead their location in memory shows their type. The value 0, in the cell #0, stands for both zero, false, and the empty list (it is breakable but mostly works).

The machine can be run using a script in a file, which it executes and then exits, or in a "repl" mode, where the user can input a script piecemeal: the machine executes as many operations as it has been given and then keeps its state waiting for further input. Exit the loop with CTRL-D. Scripts (or script fragments) must be written as Lisp lists within parentheses or square brackets. Symbols can be written in either case: they are read as uppercase.

The basic operations are supported, as well as NIL and T, and some more comparison operators (GT, LT, GEQ), and a couple of utility operations like SWAP (swaps the two values on the top of the stack), UNCONS (splits a cons into two values on the top of the stack) and DUP (duplicates the top value on the stack). A small script repository is in the directory `scripts`. The scripts are rudimentary and mostly pointless other than as an illustration of execution.

### Lisp support
To support the machine, the following Lisp functions have been implemented: cons, car, cdr, rplaca (setf (car ...) ...), rplacd (setf (cdr ...) ...) (not actually used, but included for symmetry), print(value), print(pair), read(value), and read(pair).

## Operations
Operations are described in terms of the register transitions they cause.

NIL: S  E  NIL.C  D  -->  0.S  E  C  D

I.e. pop the NIL opcode off the control register and push 0 onto the stack.

T:   S  E  T.C  D  -->  1.S  E  C  D

LD (load variable):

S  E  (LD p.C)  D  -->  (locate(p, E))  E  C  D

LDC (load constant):

S  E  (LDC x.C)  D  -->  x.S  E  C  D

ATOM (atomicity predicate):

x.S  E  ATOM.C  D  -->  t.S  E  C  D -- where t is 1 if x is an atom, otherwise 0

NOT (logical negation):

x.S  E  NOT.C  D  -->  t.S  E  C  D   -- where t is 1 if x is 0, otherwise 0

ADD, SUB, MUL, DIV, REM, GT, GEQ, LT, LEQ, EQ (arithmetic and comparison operators):

(x y.S)  E  op.C  D  -->  (y op x).S  E  C  D

CAR (car operation):

(a.b).S  E  CAR.C  D  -->  a.S  E  C  D

CDR (cdr operation):

(a.b).S  E  CDR.C  D  -->  b.S  E  C  D

CONS (cons operation):

(a b.S)  E  CONS.C  D  -->  (a.b).S  E  C  D

SEL (selection branching):

x.S  E  (SEL ct cf.C)  D  -->  S  E  cx  C.D  -- where cx is ct if x is true, otherwise cf

JOIN (end branching):

S  E  JOIN.c  C.D  -->  S  E  C  D

LDF (load closure):

S  E  (LDF f.C)  D  -->  (f.E).S  E  C  D

AP (apply function):

((f.e) v.S)  E  AP.C  D  -->  0  (v.e)  f  (S E C.D)

RTN (return):

x.s  e  RTN.c  (S E C.D)  -->  x.S  E  C  D

DUM (insert dummy layer in environment):

S  E  DUM.C  D  -->  S  0.E  C  D

RAP (apply recursive function):

(f.(0.E)) v.S)  0.E  RAP.C  D  -->  0  rplaca((0.E), v)  f  (S E C.D) -- where rplaca changes the car of the pair, inserting v

STOP (stop execution):

Just stop and report the value on the top of the stack, as well as the number of ints and conses stored during execution.

SWAP (swap values):

(a b.S)  E  SWAP.C  D  -->  (b a.S) E  C  D

UNCONS (undo cons cell):

((a.b).S)  E  UNCONS.C  D  -->  (a b.S)  E  C  D

DUP (duplicate top value):

x.S  E  DUP.C  D  -->  (x x.S)  E  C  D

## See also
- https://github.com/zachallaun/secd: a richer implementation of the machine.
- https://pqnelson.github.io/org-notes/comp-sci/abstract-machines/secd.html
- https://poincare.matf.bg.ac.rs/~smalkov//files/old/fp.r344.2016/public/predavanja/FP.cas.2016.08.SECD.pdf
- https://prism.ucalgary.ca/items/4f3ffa11-cc24-4ce6-b42b-6a54020d2ede: this one was my main reference, though not my implementation guideline.
