#include "secd.h"
#include "int.h"

int16_t getIntVal(uint8_t addr) {
    // take a memory reference, return an integer value
    if (addr < 32)
        return addr;
    else if (addr < BASE_CONS_CELL)
        return mem[addr];
    else {
        printf("Value is not an integer.");
        exit(1);
    }
}

uint8_t storeInt(int16_t val) {
    // take an integer value, return a memory reference that recalls it
    if (0 <= val && val < 32)
        return val;
    else {
        // traverse int-space to find an equal value to return, or allocate a new int
        for (uint8_t addr = 32; addr < BASE_CONS_CELL; addr++) {
            if (mem[addr] == val)
                return addr;
            else if (mem[addr] == 0) {
                // empty integer slot, store here
                mem[addr] = val;
                return addr;
            }
        }
        printf("Out of integer memory space.");
        exit(1);
    }
}

