#include "secd.h"
#include "int.h"

int getIntVal(int addr) {
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

int storeInt(int val) {
    // take an integer value, return a memory reference that recalls it
    if (0 <= val && val < 32)
        return val;
    else {
        // traverse int-space to find an equal value to return, or allocate a new int
        for (int addr = 32; addr < BASE_CONS_CELL; addr++) {
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

