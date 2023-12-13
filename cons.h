#ifndef secd_cons_h
#define secd_cons_h

int car(int cc);
int cdr(int cc);
int cons(int a, int b);
void rplaca(int addr, int val);
void rplacd(int addr, int val);

extern int16_t mem[];

extern int16_t fp;

#endif
