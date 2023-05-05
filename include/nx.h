#ifdef __SWITCH__
#ifndef NX_H 
#define NX_H 

#include <switch.h>

#define SWITCH_A        00
#define SWITCH_B        01
#define SWITCH_UP       13
#define SWITCH_DOWN     15
#define SWITCH_LEFT     12
#define SWITCH_RIGHT    14
#define SWITCH_PLUS     10

// nx-link functions for debugging
void initNxlink();
void closeNxlink();


#endif
#endif
