/**
***  brain.h
***
***    module:   brain  −  header file
***    function: The brain, i.e. the part (thread) which compute things.
***    author:   Maëlan (aka Maëlan44)
***
**/

#ifndef INCLUDED_HANOIC_BRAIN_2012_08_20_19_31_MM
#define INCLUDED_HANOIC_BRAIN_2012_08_20_19_31_MM

#include "hanoic.h"
#include <stdbool.h>
#include <string.h>
#include <unistd.h>





#define  MAX_MOVES  ( 1<<MAX_N )

typedef struct {
	unsigned cur;
	Move mv[MAX_MOVES];
} MoveStack;





void*  brainProc
  (void*);



#endif    /* header not included */
