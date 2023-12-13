#include "secd.h"
#include "cons.h"
#include "read.h"
#include "int.h"
#include "print.h"

uint8_t S, E, C, D;

int16_t mem[256];
uint8_t fp;

char *OPCODES[] = {
    "NIL", "T", "LD", "LDC", "ATOM", "NOT", "ADD", "SUB", "MUL", "DIV", "REM",
    "GT", "GEQ", "LT", "LEQ", "EQ", "CAR", "CDR", "CONS", "SEL", "JOIN", "LDF",
    "AP", "RTN", "DUM", "RAP", "STOP", "SWAP", "UNCONS", "DUP", "", "", ""
};

const char *sp;

void resetVM() {
    S = 0;
    E = 0;
    C = 0;
    D = 0;
}

void resetMem() {
    // repopulate the small integer part of memory
    for (int i = 0; i < 32; i++) {
        mem[i] = i;
    }
    // clear the big integer and cons cell parts of memory
    for (int i = 32; i <= 255; i++) {
        mem[i] = 0;
    }
    fp = BASE_CONS_CELL - 1;
}

uint8_t locate(uint8_t p, uint8_t e) {
    // take a packed pair of indices and an environment, return a variable value
    uint8_t m = car(p);
    uint8_t n = cdr(p);
    // e is a list of lists
    for (uint8_t i = 1; i < m; i++) {
        e = cdr(e);
    }
    e = car(e);
    // e is a list of values
    for (uint8_t i = 1; i < n; i++) {
        e = cdr(e);
    }
    return car(e);
}

void runTransitions() {
    // execute the operations stored in C one by one
    uint8_t a, b, x, ct, cf, f, v, c, e, p;
    for (;;) {
        if (C == 0) {
            return;
        }
        uint8_t op = car(C);
        printf("Executing %s\n", OPCODES[op]);
        C = cdr(C);
        switch (op) {
            case 0: // NIL
                S = cons(0, S);
                break;
            case 1: // T
                S = cons(1, S);
                break;
            case 2: // LD
                p = car(C); C = cdr(C);
                S = cons(locate(p, E), S);
                break;
            case 3: // LDC
                x = car(C); C = cdr(C);
                S = cons(x, S);
                break;
            case 4: // ATOM
                rplaca(S, car(S) > 0 && car(S) < BASE_CONS_CELL);
                break;
            case 5: // NOT
                rplaca(S, !car(S));
                break;
            case 6: // ADD
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(storeInt(getIntVal(b) + getIntVal(a)), S);
                break;
            case 7: // SUB
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(storeInt(getIntVal(b) - getIntVal(a)), S);
                break;
            case 8: // MUL
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(storeInt(getIntVal(b) * getIntVal(a)), S);
                break;
            case 9: // DIV
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(storeInt(getIntVal(b) / getIntVal(a)), S);
                break;
            case 10: // REM
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(storeInt(getIntVal(b) % getIntVal(a)), S);
                break;
            case 11: // GT
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(storeInt(getIntVal(b) > getIntVal(a)), S);
                break;
            case 12: // GEQ
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(storeInt(getIntVal(b) >= getIntVal(a)), S);
                break;
            case 13: // LT
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(storeInt(getIntVal(b) < getIntVal(a)), S);
                break;
            case 14: // LEQ
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(storeInt(getIntVal(b) <= getIntVal(a)), S);
                break;
            case 15: // EQ
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(a == b, S);
                break;
            case 16: // CAR
                a = car(S); S = cdr(S);
                S = cons(car(a), S);
                break;
            case 17: // CDR
                a = car(S); S = cdr(S);
                S = cons(cdr(a), S);
                break;
            case 18: // CONS
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(cons(a, b), S);
                break;
            case 19: // SEL
                x = car(S); S = cdr(S);
                ct = car(C); C = cdr(C);
                cf = car(C); C = cdr(C);
                D = cons(C, D);
                C = x ? ct : cf;
                break;
            case 20: // JOIN
                C = car(D);
                D = cdr(D);
                break;
            case 21: // LDF
                c = car(C); C = cdr(C);
                S = cons(cons(c, E), S);
                break;
            case 22: // AP
                c = car(S); S = cdr(S);
                f = car(c);
                e = cdr(c);
                v = car(S); S = cdr(S);
                D = cons(C, D);
                D = cons(E, D);
                D = cons(S, D);
                S = 0;
                C = f;
                E = cons(v, e);
                break;
            case 23: // RTN
                x = car(S);
                S = car(D); D = cdr(D);
                E = car(D); D = cdr(D);
                C = car(D); D = cdr(D);
                S = cons(x, S);
                break;
            case 24: // DUM
                E = cons(0, E);
                break;
            case 25: // RAP
                c = car(S); S = cdr(S);
                f = car(c);
                e = cdr(c);
                v = car(S); S = cdr(S);
                D = cons(C, D);
                D = cons(cdr(E), D);
                D = cons(S, D);
                S = 0;
                C = f;
                E = e;
                rplaca(E, v);
                C = c;
                break;
            case 26: // STOP
                printf("Stopping, result is: ");
                printValue(car(S));
                printf("\n");
                resetVM();
                return;
            case 27: // SWAP
                a = car(S); S = cdr(S);
                b = car(S); S = cdr(S);
                S = cons(b, cons(a, S));
                break;
            case 28: // UNCONS
                p = car(S); S = cdr(S);
                S = cons(car(p), cons(cdr(p), S));
                break;
            case 29: // DUP
                S = cons(car(S), S);
                break;

        }
        printf("S: "); printValue(S); printf("\n");
        printf("E: "); printValue(E); printf("\n");
        printf("C: "); printValue(C); printf("\n");
        printf("D: "); printValue(D); printf("\n\n");
    }
}

void repl() {
    // endlessly read from stdin, compile, and execute
    // adapted from Robert Nystrom, Crafting Interpreters
    char line[80];
    for (;;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }

        sp = line;
        C = readValue();
        runTransitions();
    }
}

uint8_t compileScript(const char *source) {
    // take a source text pointer, print the source, compile it, print
    // the compiled source, and return a pointer to the compiled source.
    printf("Source code:\n%s\n\n", source);
    sp = source;
    uint8_t c = readValue();
    printf("Compiled to:\n");
    printValue(c); printf("\n\n");
    return c;
}

int main (int argc, const char* argv[]) {
    resetVM();
    resetMem();

    if (argc == 1)
        repl();
    else if (argc == 2) {
        char *source = readFile(argv[1]);
        C = compileScript(source);
        runTransitions();
        free(source);
    } else {
        fprintf(stderr, "Usage: secd [path]\n");
        exit(1);
    }

}


