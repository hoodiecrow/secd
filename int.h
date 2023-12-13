#ifndef secd_int_h
#define secd_int_h

int16_t getIntVal(uint8_t addr);
uint8_t storeInt(int16_t val);

extern int16_t mem[];

#endif
