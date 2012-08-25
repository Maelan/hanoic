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





WINDOW*  boardWin = NULL;



GraphicPosition  gpos = {
	.h = { 0, 0, 0 }
};



Selection  sel = {
	.n = 0,
	.cur = 1
};





void  initBoardWin
  (void)
{
	boardWin = newwin(BOARDWIN_H, BOARDWIN_W, BOARDWIN_Y, BOARDWIN_X);
	/*keypad(boardWin, true);
	nodelay(boardWin, true);*/
	
	wattron(boardWin, COLOR_PAIR(20));
}



void  endBoardWin
	(void)
{
	delwin(boardWin);
}



void  updateBoard
  (Position const* pos)
{
	/* Update the datas. */
	gpos.n = pos->n;
	gpos.h[0] = 0;
	gpos.h[1] = 0;
	gpos.h[2] = 0;
	for(unsigned i = 0;  i < pos->n;  i++)
		gpos.pegs[pos->pos[i]-1][gpos.h[pos->pos[i]-1]++] = pos->n-i;    /* RoOooOoock! */
	
	wclear(boardWin);
	overlay(numWin, boardWin);
	
	/* Draw the 3 pegs. */
	for(unsigned i = 0;  i < 3;  i++)
		mvwvline(boardWin, GAP_Y, (2*MAX_N+1+GAP_X)*i + MAX_N, '|', MAX_N);
	/* Draw the disks. */
	for(unsigned i = 0;  i < 3;  i++)
		for(unsigned j = 0;  j < gpos.h[i];  j++)
			drawDisk(gpos.pegs[i][j], i+1, j+1, true);
	/*  Show the “cursor”.*/
	moveCursor(1);
	
	wrefresh(boardWin);
}



void  drawDisk
  (unsigned n, unsigned peg, unsigned h, bool draw)
{
	wmove(boardWin, BOARDWIN_H-1-h, (2*MAX_N+1+GAP_X)*(peg-1)+MAX_N+n-(n>9));
	if(draw)
		wprintw(boardWin, "%u", n);
	else
		wprintw(boardWin, "  ");
	mvwchgat(boardWin, BOARDWIN_H-1-h, (2*MAX_N+1+GAP_X)*(peg-1)+MAX_N-n,
	  2*n+1, (draw ? A_BOLD : A_NORMAL), (draw ? n%8+1 : 20), NULL);
	wrefresh(boardWin);
}



void  teleportDisk
  (unsigned n, unsigned src, unsigned hSrc, unsigned dest, unsigned hDest)
{
	drawDisk(n, src, hSrc, false);
	drawDisk(n, dest, hDest, true);
}



void  moveDisk
  (Move const* mv)
{
	unsigned n = gpos.pegs[mv->src-1][gpos.h[mv->src-1]-1];
	
	gpos.h[mv->src-1]--;
	gpos.h[mv->dest-1]++;
	gpos.pegs[mv->dest-1][gpos.h[mv->dest-1]-1] = n;
	
	teleportDisk( n,
	  mv->src, gpos.h[mv->src-1]+1,
	  mv->dest, gpos.h[mv->dest-1] );
}



void  moveCursor
  (unsigned newCur)
{
	mvwhline(boardWin, BOARDWIN_H-1, (2*MAX_N+1+GAP_X)*(sel.cur-1), ' ', 2*MAX_N+1);
	mvwhline(boardWin, BOARDWIN_H-1, (2*MAX_N+1+GAP_X)*(newCur-1), ':', 2*MAX_N+1);
	wrefresh(boardWin);
	
	sel.cur = newCur;
}



void  selectDisk
  (void)
{
	if(!gpos.h[sel.cur-1])
		return;
	
	sel.orig = sel.cur;
	sel.n = gpos.pegs[sel.cur-1][gpos.h[sel.cur-1]-1];
	gpos.h[sel.cur-1]--;
	
	teleportDisk(sel.n, sel.cur, gpos.h[sel.cur-1]+1, sel.cur, MAX_N+GAP_Y);
}



void  releaseDisk
  (void)
{
	if(gpos.h[sel.cur-1]  &&  sel.n > gpos.pegs[sel.cur-1][gpos.h[sel.cur-1]-1])
		return;
	
	teleportDisk(sel.n, sel.orig, MAX_N+GAP_Y, sel.cur, gpos.h[sel.cur-1]+1);
	
	if(sel.cur != sel.orig) {
		Signal sig = {
			.type = SIG_NEWMOVE,
			.mv = { .src = sel.orig, .dest = sel.cur }
		};
		sendSignal(&brain, &sig);
	}
	
	gpos.pegs[sel.cur-1][gpos.h[sel.cur-1]] = sel.n;
	gpos.h[sel.cur-1]++;
	sel.n = 0;
}



void  toggleSelected
  (void)
{
	if(sel.n)
		releaseDisk();
	else
		selectDisk();
}



void  attemptMove
  (unsigned peg1, unsigned peg2)
{
	Signal sig;
	Move mv;
	unsigned n1 = (gpos.h[peg1-1]) ? gpos.pegs[peg1-1][gpos.h[peg1-1]-1] : MAX_N+1,
	         n2 = (gpos.h[peg2-1]) ? gpos.pegs[peg2-1][gpos.h[peg2-1]-1] : MAX_N+1;
	
	if(n1 == n2)          /* nothing (both pegs are empty) */
		return;
	else if(n1 < n2) {    /* peg1 → peg2 */
		//mv.n = n1;
		mv.src = peg1;
		mv.dest = peg2;
	}
	else {                /* peg1 ← peg2 */
		//mv.n = n2;
		mv.src = peg2;
		mv.dest = peg1;
	}
	
	sig.type = SIG_NEWMOVE;
	sig.mv = mv;
	sendSignal(&brain, &sig);
	
	moveDisk(&mv);
}
