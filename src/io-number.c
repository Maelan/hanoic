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



void  printNumber
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
				waddch(numWin, digits[*p-'0'][i*(digitsWidth[*p-'0']+1) + j]);
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

static size_t const  digitsWidth[10] = { 6, 7, 6, 6, 7, 6, 6, 6, 6, 6 };

static char const*  digits[10] = {

	" ###  \n"
	"## ## \n"
	"## ## \n"
	"## ## \n"
	"## ## \n"
	"## ## \n"
	" ###  \n",
	
	"  ##   \n"
	"####   \n"
	"  ##   \n"
	"  ##   \n"
	"  ##   \n"
	"  ##   \n"
	"###### \n",
	
	" ###  \n"
	"## ## \n"
	"   ## \n"
	"  ##  \n"
	" ##   \n"
	"## ## \n"
	"##### \n",
	
	" ###  \n"
	"## ## \n"
	"   ## \n"
	" ###  \n"
	"   ## \n"
	"## ## \n"
	" ###  \n",
	
	"   ##  \n"
	"  ###  \n"
	" # ##  \n"
	"## ##  \n"
	"###### \n"
	"   ##  \n"
	"   ##  \n",
	
	"##### \n"
	"##    \n"
	"####  \n"
	"## ## \n"
	"   ## \n"
	"#  ## \n"
	"####  \n",
	
	" ###  \n"
	"## ## \n"
	"##    \n"
	"####  \n"
	"## ## \n"
	"## ## \n"
	" ###  \n",
	
	"##### \n"
	"## ## \n"
	"   ## \n"
	"  ##  \n"
	"  ##  \n"
	" ##   \n"
	" ##   \n",
	
	" ###  \n"
	"## ## \n"
	"## ## \n"
	" ###  \n"
	"## ## \n"
	"## ## \n"
	" ###  \n",
	
	" ###  \n"
	"## ## \n"
	"## ## \n"
	" #### \n"
	"   ## \n"
	"## ## \n"
	" ###  \n"
};
