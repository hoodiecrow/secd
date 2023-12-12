#ifndef secd_read_h
#define secd_read_h

bool findRPar();
int readPair();
int readValue();
int readOpcode();
int readNumber();

char* readFile(const char* path);

extern const char *sp;
extern char *OPCODES[];

#endif
