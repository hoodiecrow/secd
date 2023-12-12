#ifndef secd_cons_h
#define secd_cons_h

int car(int cc);
int cdr(int cc);
int cons(int a, int b);
void setcar(int addr, int val);
void setcdr(int addr, int val);

extern int mem[];

#endif
