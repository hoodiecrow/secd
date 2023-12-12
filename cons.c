#include "secd.h"
#include "cons.h"

int car(int addr) {
    // take an address, return the car of the stored value
    if (addr < BASE_CONS_CELL) {
        printf("Not a cons cell: %d", addr);
        exit(1);
    }
    return (mem[addr] & 0xff00) >> 8;
}

int cdr(int addr) {
    // take an address, return the cdr of the stored value
    if (addr < BASE_CONS_CELL) {
        printf("Not a cons cell: %d", addr);
        exit(1);
    }
    return mem[addr] & 0xff;
}

int cons(int a, int b) {
    // take two values, return the cons of both
    if (fp == 255) {
        printf("Out of cons memory space.");
        exit(1);
    }
    mem[++fp] = (a << 8) | (b & 0xff);
    return fp;
}

void setcar(int addr, int val) {
    // take an address and a value, modify the car of the stored value
    mem[addr] = (val << 8) | (mem[addr] & 0xff);
}

void setcdr(int addr, int val) {
    // take an address and a value, modify the cdr of the stored value
    mem[addr] = (mem[addr] & 0xff00) | (val & 0xff);
}


