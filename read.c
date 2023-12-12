#include "secd.h"
#include "read.h"
#include "cons.h"
#include "int.h"

static void skipWhitespace() {
    // move the source pointer past whitespace and comments
    // adapted from Robert Nystrom, Crafting Interpreters
    for (;;) {
        char c = *sp;
        switch (c) {
        case ' ':
        case '\r':
        case '\t':
        case '\n':
            sp++;
            break;
        case ';':
            // a comment goes on until the end of the line
            while (*sp != '\n' && *sp != 0)
                sp++;
            break;
        default:
            return;
        }
    }
}

bool findC(int c) {
    // take a character, peek beyond whitespace to find it
    const char *cp = sp;
    while (isspace(*cp))
        cp++;
    return *cp == c;
}

int readPair(int c) {
    // take a character, read a car and a cdr value, pass the char to findC
    int a, d;
    skipWhitespace();
    a = readValue();
    if (strncmp(" . ", sp, 3) == 0) {
        sp += 3;
        skipWhitespace();
        d = readValue();
    } else if (findC(c)) {
        skipWhitespace();
        d = 0;
    } else {
        skipWhitespace();
        d = readPair(c);
    }
    skipWhitespace();
    return cons(a, d);
}

int readOpcode() {
    // take an input token, return a small-integer opcode number
    // An opcode is up to 6 letters long and is
    // case-insensitive on input (normalised to uppercase).
    // It is coded by its place in the OPCODES array 
    char buf[7];
    int i;
    for (i = 0; i < 7; i++) {
        if (isalpha(*sp))
            buf[i] = toupper(*sp++);
        else
            break;
    }
    buf[i] = 0;
    for (int s = 0; s < 32; s++)
        if (strcmp(buf, OPCODES[s]) == 0)
            return s;
    printf("Unrecognised symbol %s\n", buf);
    exit(1);
}

int readNumber() {
    // take an input token, return an integer memory reference code
    int sign;
    int n;
    if (*sp == '-') {
        sign = -1;
        ++sp;
    } else
        sign = 1;
    n = *sp-'0';
    while (isdigit(*++sp)) {
        n = 10 * n + *sp-'0';
    }
    n *= sign;
    if (n >= 0 && n < 32)
        return n;
    else
        return storeInt(n);
}

int readValue() {
    // take an input token, return a value (integer or cons cell)
    skipWhitespace();
    if (isalpha(*sp)) {
        return readOpcode();
    } else if (*sp == '-' || isdigit(*sp)) {
        return readNumber();
    } else if (*sp == '(') {
        ++sp;
        skipWhitespace();
        int p = readPair(')');
        skipWhitespace();
        if (*sp++ != ')') {
            printf("Missing right parenthesis.");
            exit(1);
        }
        return p;
    } else if (*sp == '[') {
        // same as above, but with [] instead of ()
        ++sp;
        skipWhitespace();
        int p = readPair(']');
        skipWhitespace();
        if (*sp++ != ']') {
            printf("Missing right square bracket.");
            exit(1);
        }
        return p;
    }
    return 0;
}

char* readFile(const char* path) {
    // take a file name, read a source text (to be free:ed)
    // borrowed from Robert Nystrom's Crafting Interpreters
    FILE* file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(1);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char* buffer = malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(1);
    }

    size_t bytesRead = fread(buffer, 1, fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(1);
    }
    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}


