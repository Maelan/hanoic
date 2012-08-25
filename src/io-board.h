/**
***  io-board.h
***
***    module:   io  −  header file
***    function: The interaction module (thread), which listen what the user do
***              and draw beautiful things onto the screen.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#ifndef INCLUDED_HANOIC_IO_BOARD_2012_08_20_19_31_MM
#define INCLUDED_HANOIC_IO_BOARD_2012_08_20_19_31_MM

#include "io.h"
#include "hanoic.h"
#include <ncurses.h>





#define  BOARDWIN_X  GAP_X
#define  BOARDWIN_Y  2
#define  BOARDWIN_W  (80 - BOARDWIN_X)
#define  BOARDWIN_H  (MAX_N + GAP_Y + 1)
#define  GAP_X       ( (80 - 3*(2*MAX_N+1)) / 4 )
#define  GAP_Y       2



extern WINDOW*  boardWin;



/* A more precise description of a position (“board”), useful for drawing. */
typedef struct {
	unsigned h[3];          /* “height” of (number of disks on) each peg */
	char pegs[3][MAX_N];    /* disks stacked on the pegs */
} GraphicPosition;

extern GraphicPosition  gpos;



/* A “selection” of a peg or disk in the user inteface. */
typedef struct {
	unsigned n;       /* number of the selected disk (0 if no selection) */
	unsigned orig,    /* peg from which the selcted disk comes */
	         cur;     /* current peg */
} Selection;

extern Selection  sel;



void  initBoardWin
  (void);


void  endBoardWin
	(void);


void  updateBoard
  (Position const* pos);


void  drawDisk
  (unsigned n, unsigned peg, unsigned h, bool draw);


void  teleportDisk
  (unsigned n, unsigned src, unsigned hSrc, unsigned dest, unsigned hDest);


void  moveDisk
  (Move const* mv);


void  moveCursor
  (unsigned newCur);


void  selectDisk
  (void);


void  releaseDisk
  (void);


void  toggleSelected
  (void);


void  attemptMove
  (unsigned peg1, unsigned peg2);



#endif    /* header not included */
