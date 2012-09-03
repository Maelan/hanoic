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





WINDOW*  numWin = NULL;





static size_t const  digitsHeight;

static size_t const  digitsWidth[10];

static char const*  digits[10];





void  initNumWin
  (void)
{
	numWin = newwin(NUMWIN_H, NUMWIN_W, NUMWIN_Y, NUMWIN_X);
	
	wattron(numWin, COLOR_PAIR(20));
	wrefresh(numWin);
}



void  endNumWin
  (void)
{
	delwin(numWin);
}



void  updateNumber
  (unsigned n)
{
	char buf[10];
	unsigned off;
	
	snprintf(buf, sizeof(buf)/sizeof(*buf), "%u", n);
	
	wclear(numWin);
	
	off = 0;
	for(char const* p = buf;  *p;  p++) {
		for(size_t i = 0;  i < digitsHeight;  i++) {
			wmove(numWin, i, off);
			for(size_t j = 0;  j < digitsWidth[*p-'0'];  j++)
				waddch(numWin, digits[*p-'0'][i*(digitsWidth[*p-'0']) + j]);
		}
		off += digitsWidth[*p-'0'];
	}
	
	wrefresh(numWin);
}





/*
 ###    ##    ###   ###     ##  #####  ###  #####  ###   ###  
## ## ####   ## ## ## ##   ###  ##    ## ## ## ## ## ## ## ## 
## ##   ##      ##    ##  # ##  ####  ##       ## ## ## ## ## 
## ##   ##     ##   ###  ## ##  ## ## ####    ##   ###   #### 
## ##   ##    ##      ## ######    ## ## ##   ##  ## ##    ## 
## ##   ##   ## ## ## ##    ##  #  ## ## ##  ##   ## ## ## ## 
 ###  ###### #####  ###     ##  ####   ###   ##    ###   ###  
*/

static size_t const  digitsHeight = 7;

static size_t const  digitsWidth[10] = { 11, 6, 11, 11, 11, 11, 11, 11, 11, 11 };

static char const*  digits[10] = {


	"  .oooo.   "
	" d8P'`Y8b  "
	"888    888 "
	"888    888 "
	"888    888 "
	"`88b  d88' "
	" `Y8bd8P'  "
,	
	"  .o  "
	"o888  "
	" 888  "
	" 888  "
	" 888  "
	" 888  "
	"o888o "
,	
	"  .oooo.   "
	".dP\"\"Y88b  "
	"      ]8P' "
	"    .d8P'  "
	"  .dP'     "
	".oP     .o "
	"8888888888 "
,	
	"  .oooo.   "
	".dP\"\"Y88b  "
	"      ]8P' "
	"    <88b.  "
	"     `88b. "
	"o.   .88P  "
	"`8bd88P'   "
,	
	"      .o   "
	"    .d88   "
	"  .d'888   "
	".d'  888   "
	"88ooo888oo "
	"     888   "
	"    o888o  "
,	
	"  oooooooo "
	" dP\"\"\"\"\"\"\" "
	"d88888b.   "
	"    `Y88b  "
	"      ]88  "
	"o.   .88P  "
	"`8bd88P'   "
,	
	"    .ooo   "
	"  .88'     "
	" d88'      "
	"d888P\"Ybo. "
	"Y88[   ]88 "
	"`Y88   88P "
	" `88bod8'  "
,	
	" ooooooooo "
	"d\"\"\"\"\"\"\"8' "
	"      .8'  "
	"     .8'   "
	"    .8'    "
	"   .8'     "
	"  .8'      "
,	
	" .ooooo.   "
	"d88'   `8. "
	"Y88..  .8' "
	" `88888b.  "
	".8'  ``88b "
	"`8.   .88P "
	" `boood8'  "
,	
	"  .ooooo.  "
	"888' `Y88. "
	"888    888 "
	" `Vbood888 "
	"      888' "
	"    .88P'  "
	"  .oP'     "
};
