#ifndef secd_read_h
#define secd_read_h

bool findRPar();
int readPair();
int readValue();
int readOpcode();
int readNumber();

char* readFile(const char* path);

// pointer to the current character in the source
extern const char *sp;

// list of opcode names in coding order
extern char *OPCODES[];

#endif
