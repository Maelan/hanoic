/**
***  hanoic.h
***
***    module:   hanoic  −  header file
***    function: The main program.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#ifndef INCLUDED_HANOIC_2012_08_20_19_31_MM
#define INCLUDED_HANOIC_2012_08_20_19_31_MM



#define  MAX_N      12
#define  DEFAULT_N  4



typedef struct Move {
	char src, dest;
	//unsigned char n;
} Move;



typedef struct {
	unsigned n;
	char* pos;
} Position;



#include "threads.h"
#include "brain.h"    /* That’s better. */
#include "io.h"





//extern Thread  brain, io;





int  main
  (int ac, char** av);



#endif    /* header not included */
