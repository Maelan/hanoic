/**
***  io-number.h
***
***    module:   io  −  header file
***    function: The interaction module (thread), which listen what the user do
***              and draw beautiful things onto the screen.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#ifndef INCLUDED_HANOIC_IO_NUMBER_2012_08_20_19_31_MM
#define INCLUDED_HANOIC_IO_NUMBER_2012_08_20_19_31_MM

#include "io.h"
#include <ncurses.h>





#define  DIGIT_HEIGHT     7
#define  DIGIT_MAXWIDTH  11



#define  NUMWIN_X   0
#define  NUMWIN_Y   0
#define  NUMWIN_W  (2*DIGIT_MAXWIDTH)
#define  NUMWIN_H   DIGIT_HEIGHT



extern WINDOW *numWin;



void  initNumWin
  (void);


void  endNumWin
  (void);


void  updateNumber
  (unsigned n);



#endif    /* header not included */
