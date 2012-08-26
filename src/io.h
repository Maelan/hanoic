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

#include "io-number.h"
#include "io-board.h"
#include "io-stats.h"
#include "hanoic.h"
#include <ncurses.h>
#include <stdbool.h>
#include <unistd.h>





void*  ioProc
  (void*);



#endif    /* header not included */
