/**
***  io-stats.h
***
***    module:   io  −  header file
***    function: The interaction module (thread), which listen what the user do
***              and draw beautiful things onto the screen.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#ifndef INCLUDED_HANOIC_IO_STATS_2012_08_20_19_31_MM
#define INCLUDED_HANOIC_IO_STATS_2012_08_20_19_31_MM

#include "io.h"
#include "hanoic.h"
#include <ncurses.h>





#define  STATSWIN_X  45
#define  STATSWIN_Y   0
#define  STATSWIN_W  36
#define  STATSWIN_H   2



extern WINDOW*  statsWin;



void  initStatsWin
	(void);


void  endStatsWin
	(void);


void  updateStatitsics
  (Statistics const* stats);



#endif    /* header not included */
