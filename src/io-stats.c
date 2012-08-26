/**
***  io.c
***
***    module:   io  −  source file
***    function: The interaction module (thread), which listen what the user do
***              and draw beautiful things onto the screen.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#include "io.h"





WINDOW*  statsWin = NULL;





void  initStatsWin
  (void)
{
	statsWin = newwin(STATSWIN_H, STATSWIN_W, STATSWIN_Y, STATSWIN_X);
	
	waddstr(statsWin,
	  "   you      |      optimal solution\n"
	  "errors      |      from now" );
	
	/* Emphasis over “you” and “optimal”. */
	mvwchgat(statsWin, 0,  3,  3, A_BOLD, 0, NULL);    /* “you” */
	mvwchgat(statsWin, 0, 19,  7, A_BOLD, 0, NULL);    /* “optimal” */
}



void  endStatsWin
  (void)
{
	delwin(statsWin);
}



void  updateStatistics
  (Statistics const* stats)
{
	mvwprintw(statsWin, 0,  7,  "% 4u", stats->done);       /* you */
	mvwprintw(statsWin, 1,  7,  "% 4u", stats->errors);     /* errors */
	mvwprintw(statsWin, 0, 14,  "%-4u", stats->initial);    /* optimal */
	mvwprintw(statsWin, 1, 14,  "%-4u", stats->fromNow);    /* from now */
	
	/* Color over these numbers. :) */
	mvwchgat(statsWin, 0,  7,  4, A_BOLD, 10, NULL);    /* you */
	mvwchgat(statsWin, 1,  7,  4, A_BOLD, 11, NULL);    /* errors */
	mvwchgat(statsWin, 0, 14,  4, A_BOLD, 12, NULL);    /* optimal */
	mvwchgat(statsWin, 1, 14,  4, A_BOLD, 13, NULL);    /* from now */
	
	wrefresh(statsWin);
}
