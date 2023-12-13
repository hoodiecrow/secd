#ifndef secd_cons_h
#define secd_cons_h

uint8_t car(uint8_t cc);
uint8_t cdr(uint8_t cc);
uint8_t cons(uint8_t a, uint8_t b);
void rplaca(uint8_t addr, uint8_t val);
void rplacd(uint8_t addr, uint8_t val);

extern int16_t mem[];

extern uint8_t fp;

#endif
