#include "secd.h"
#include "cons.h"

uint8_t car(uint8_t addr) {
    // take an address, return the car of the stored value
    if (addr < BASE_CONS_CELL) {
        printf("Not a cons cell: %d", addr);
        exit(1);
    }
    return (mem[addr] >> 8) & 0xff;
}

uint8_t cdr(uint8_t addr) {
    // take an address, return the cdr of the stored value
    if (addr < BASE_CONS_CELL) {
        printf("Not a cons cell: %d", addr);
        exit(1);
    }
    return mem[addr] & 0xff;
}

uint8_t cons(uint8_t a, uint8_t b) {
    // take two values, return the cons of both
    if (fp == 255) {
        printf("Out of cons memory space.");
        exit(1);
    }
    mem[++fp] = (a << 8) | b;
    return fp;
}

void rplaca(uint8_t addr, uint8_t val) {
    // take an address and a value, modify the car of the stored value
    mem[addr] = (val << 8) | (mem[addr] & 0xff);
}

void rplacd(uint8_t addr, uint8_t val) {
    // take an address and a value, modify the cdr of the stored value
    mem[addr] = (mem[addr] & 0xff00) | val;
}


