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





static WINDOW*  playWin = NULL;



static GraphicPosition  gpos = {
	.h = { 0, 0, 0 }
};



static Selection  sel = {
	.n = 0,
	.cur = 1
};



static void  drawDisk
  (unsigned n, unsigned peg, unsigned h, bool draw)
{
	wmove(playWin, PLAYWIN_H-1-h, (2*MAX_N+1+GAP_X)*(peg-1)+MAX_N+n-(n>9));
	if(draw)
		wprintw(playWin, "%u", n);
	else
		wprintw(playWin, "  ");
	mvwchgat(playWin, PLAYWIN_H-1-h, (2*MAX_N+1+GAP_X)*(peg-1)+MAX_N-n,
	  2*n+1, (draw ? A_BOLD : A_NORMAL), (draw ? n%8+1 : 0), NULL);
	wrefresh(playWin);
}



static void  teleportDisk
  (unsigned n, unsigned src, unsigned hSrc, unsigned dest, unsigned hDest)
{
	drawDisk(n, src, hSrc, false);
	drawDisk(n, dest, hDest, true);
}



static void  moveDisk
  (Move const* mv)
{
	teleportDisk( gpos.pegs[mv->src-1][gpos.h[mv->src-1]-1],
	  mv->src, gpos.h[mv->src-1],
	  mv->dest, gpos.h[mv->dest-1] );
}



static void  select
  (void)
{
	if(!gpos.h[sel.cur-1])
		return;
	
	sel.orig = sel.cur;
	sel.n = gpos.pegs[sel.cur-1][gpos.h[sel.cur-1]-1];
	gpos.h[sel.cur-1]--;
	
	teleportDisk(sel.n, sel.cur, gpos.h[sel.cur-1]+1, sel.cur, MAX_N+GAP_Y);
}



static void  release
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



static void  toggleSelected
  (void)
{
	if(sel.n)
		release();
	else
		select();
}



static void  moveCursor
  (unsigned newCur)
{
	mvwhline(playWin, PLAYWIN_H-1, (2*MAX_N+1+GAP_X)*(sel.cur-1), ' ', 2*MAX_N+1);
	mvwhline(playWin, PLAYWIN_H-1, (2*MAX_N+1+GAP_X)*(newCur-1), 0, 2*MAX_N+1);
	wrefresh(playWin);
	
	sel.cur = newCur;
}



static void  updatePosition
  (Position const* pos)
{
	/* Update the position datas. */
	gpos.h[0] = 0;
	gpos.h[1] = 0;
	gpos.h[2] = 0;
	for(unsigned i = 0;  i < pos->n;  i++)
		gpos.pegs[pos->pos[i]-1][gpos.h[pos->pos[i]-1]++] = pos->n-i;    /* RoOooOoock! */
	
	clear();
	/* Draw the 3 pegs. */
	for(unsigned i = 0;  i < 3;  i++)
		mvwvline(playWin, GAP_Y, (2*MAX_N+1+GAP_X)*i + MAX_N, '|', MAX_N);
	/* Draw the disks. */
	for(unsigned i = 0;  i < 3;  i++)
		for(unsigned j = 0;  j < gpos.h[i];  j++)
			drawDisk(gpos.pegs[i][j], i+1, j+1, true);
	/*  Show the cursor.*/
	moveCursor(1);
	wrefresh(playWin);
}



void*  ioProc
  (void* self)
{
	Signal* sig;
	Signal send;
	int c;
	bool again;
	
	initscr();
	/* Input settings. */
	timeout(0);
	cbreak();
	keypad(stdscr, true);
	mousemask(BUTTON1_CLICKED, NULL);
	noecho();
	curs_set(0);
	/* Output settings. */
	start_color();
	use_default_colors();
	for(int i = 0;  i < 8; ++i)
		init_pair(i+1, i, i);
	refresh();
	
	playWin = newwin(PLAYWIN_H, PLAYWIN_W, PLAYWIN_Y, PLAYWIN_X);
	keypad(playWin, true);
	
	again = true;
	while(again) {
		sig = getSignal(self);
		
		if(sig) {
			switch(sig->type) {
			  case SIG_END:
				again = false;
				break;
			  case SIG_NEWPOS:
				updatePosition(&sig->pos);
				break;
			  case SIG_NEWMOVE:
				moveDisk(&sig->mv);
				break;
			  default:
				break;
			}
			
			destroySignal(sig);
		}
		
		c = wgetch(playWin);
		switch(c) {
		  case 'q':
			send.type = SIG_END;
			sendSignal(&brain, &send);
			again = false;
			break;
		  case ' ':
			toggleSelected();
			break;
		  case '4':
		  case '5':
		  case '6':
			moveCursor(c-'3');
			toggleSelected();
			break;
		  case '1':
		  case '2':
		  case '3':
			moveCursor(c-'0');
			break;
		  case KEY_LEFT:
			moveCursor((sel.cur==1) ? 3 : sel.cur-1);
			break;
		  case KEY_RIGHT:
			moveCursor(sel.cur%3 + 1);
			break;
		  default:
			break;
		}
	}
	
	endwin();
	
	pthread_exit(NULL);
}
