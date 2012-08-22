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





static GraphicPosition  gpos = {
	.h = { 0, 0, 0 }
};



static Selection  sel = {
	.n = 0,
	.cur = 1
};



static void  updatePosition
  (Position const* pos)
{
	gpos.h[0] = 0;
	gpos.h[1] = 0;
	gpos.h[2] = 0;
	
	for(unsigned i = 0;  i < pos->n;  i++)
		gpos.pegs[pos->pos[i]-1][gpos.h[pos->pos[i]-1]++] = pos->n-i;    /* RoOooOoock! */
}



static void  drawDisk
  (unsigned peg, unsigned h, unsigned n, bool draw)
{
	unsigned const xoff = 1, yoff = 10;
	
	/*(draw?attron:attroff)(COLOR_PAIR(n%8));
	mvprintw(yoff+MAX_N-h, xoff+(2*MAX_N+1+2)*(peg-1),  "<-- %u -->", n);
	(draw?attroff:attron)(COLOR_PAIR(n%8));*/
	
	mvprintw(yoff+MAX_N-h, xoff+(2*MAX_N+1+2)*(peg-1),  "%u", n);
	mvchgat(yoff+MAX_N-h, xoff+(2*MAX_N+1+2)*(peg-1)+MAX_N-n,
	  2*n+1, A_NORMAL, (draw ? n%8 : 0), NULL);
	refresh();
}



static void  drawMove
  (/*Move const* mv*/unsigned n, unsigned src, unsigned hSrc, unsigned dest, unsigned hDest)
{
	/*drawDisk(mv->src-1, gpos.h[mv->src-1], gpos.pegs[mv->src-1][gpos.h[mv->src-1]-1], false);
	drawDisk(mv->dest-1, gpos.h[mv->dest-1], gpos.pegs[mv->src-1][gpos.h[mv->src-1]-1], true);*/
	drawDisk(src-1, hSrc, n, false);
	drawDisk(dest-1, hDest, n, true);
}



static void  drawPosition
  (void)
{
	clear();
	
	for(unsigned i = 0;  i < 3;  i++)
		for(unsigned j = 0;  j < gpos.h[i];  j++)
			drawDisk(i+1, j+1, gpos.pegs[i][j], true);
}



static void  select
  (void)
{
	sel.orig = sel.cur;
	sel.n = gpos.pegs[sel.cur-1][gpos.h[sel.cur-1]-1];
	gpos.h[sel.cur-1]--;
	
	/*drawDisk(sel.cur-1, gpos.h[sel.cur-1]+1, sel.n, false);
	drawDisk(sel.cur-1, MAX_N+1, sel.n, true);*/
	drawMove(sel.n, sel.cur, gpos.h[sel.cur-1], sel.cur, MAX_N+1);
}



static void  release
  (void)
{
	if(gpos.h[sel.cur]  &&  sel.n > gpos.pegs[sel.cur-1][gpos.h[sel.cur-1]-1])
		return;
	
	/*drawDisk(sel.orig-1, MAX_N+1, sel.n, false);
	drawDisk(sel.cur-1, gpos.h[sel.cur-1]+1, sel.n, true);*/
	drawMove(sel.n, sel.orig, MAX_N+1, sel.cur, gpos.h[sel.cur-1]+1);
	
	gpos.pegs[sel.cur-1][gpos.h[sel.cur-1]] = sel.n;
	gpos.h[sel.cur-1]++;
	sel.n = 0;
}



void*  ioProc
  (void* self)
{
	Signal* sig;
	Signal send;
	int c;
	bool again;
	
	printf("Kikoo c tro bi1 ici\n");
	
	/* initialisations. */
	initscr();
	/* Input initializations. */
	cbreak();
	keypad(stdscr, true);
	mousemask(BUTTON1_CLICKED, NULL);
	noecho();
	curs_set(0);
	/* Output initializations. */
	start_color();
	use_default_colors();
	for(int i = 1;  i <= 9; ++i)
		init_pair(i, -1, i);
	refresh();
	
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
				drawPosition();
				break;
			  case SIG_NEWMOVE:
				//drawMove(&sig->mv);
				break;
			  default:
				break;
			}
			
			destroySignal(sig);
		}
		
		c = getch();
		switch(c) {
		  case 'q':
			send.type = SIG_END;
			sendSignal(&brain, &send);
			again = false;
			break;
		  case ' ':
			if(sel.n)
				release();
			else
				select();
			break;
		  case '1':
		  case '2':
		  case '3':
			sel.cur = c-'0';
			mvprintw(1,1, "%u (#%u)", sel.cur, sel.n);
			break;
		  default:
			break;
		}
	}
	
	endwin();
	
	printf("slt a+!!!\n");
	pthread_exit(NULL);
}
