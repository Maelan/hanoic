/**
***  io.h
***
***    module:   io  −  header file
***    function: The interaction module (thread), which listen what the user do
***              and draw beautiful things onto the screen.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#ifndef INCLUDED_HANOIC_IO_2012_08_20_19_31_MM
#define INCLUDED_HANOIC_IO_2012_08_20_19_31_MM

#include "hanoic.h"
#include <ncurses.h>
#include <stdbool.h>





#define  PLAYWIN_X  GAP_X
#define  PLAYWIN_Y  7
#define  PLAYWIN_W  (80 - PLAYWIN_X)
#define  PLAYWIN_H  (MAX_N + GAP_Y + 1)
#define  GAP_X      ( (80 - 3*(2*MAX_N+1)) / 4 )
#define  GAP_Y      2



typedef struct {
	unsigned h[3];
	char pegs[3][MAX_N+1];
} GraphicPosition;



typedef struct {
	unsigned n;
	unsigned orig, cur;
} Selection;



void*  ioProc
  (void*);



#endif    /* header not included */
