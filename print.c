#include "secd.h"
#include "print.h"
#include "cons.h"

void printPair(int addr) {
    // take an address and print the car and the cdr of the stored value
    int a = car(addr);
    int d = cdr(addr);
    // print car
    printValue(a);
    if (d >= BASE_CONS_CELL) {
        // cdr is a cons pair
        printf(" ");
        printPair(d);
    } else if (d == 0) {
        // cdr is nil
        return;
    } else {
        // it is an atom
        printf(" . ");
        printValue(d);
    }
}

void printValue(int addr) {
    // take an address and print the value
    if (addr < 32)
        // it is a small integer
        printf("%d", addr);
    else if (addr < BASE_CONS_CELL)
        // it is a stored integer
        printf("%d", mem[addr]);
    else {
        // it is a cons pair
        printf("(");
        printPair(addr);
        printf(")");
    }
}

