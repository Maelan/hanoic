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





void*  ioProc
  (void* self)
{
	Signal* sig;
	Signal send;
	bool again;
	int c;
	
	initscr();
	/* Input settings. */
	cbreak();
	keypad(stdscr, true);
	//mousemask(BUTTON1_CLICKED, NULL);
	nodelay(stdscr, true);
	noecho();
	curs_set(0);
	/* Output settings. */
	start_color();
	use_default_colors();
	for(int i = 0;  i < 8; ++i)    /* 8 color pairs for the disks */
		init_pair(i+1, i, i);
	init_pair(10, COLOR_YELLOW, -1);    /* color pairs for statistics */
	init_pair(11, COLOR_RED,    -1);    /* … */
	init_pair(12, COLOR_GREEN,  -1);    /* … */
	init_pair(13, COLOR_BLUE,   -1);    /* … */
	init_pair(20, COLOR_BLACK,   -1);    /* color for drawings (N and pegs) */
	refresh();
	
	/* Windows. */
	initNumWin();
	initStatsWin();
	initBoardWin();
	
	again = true;
	while(again) {
		sig = getSignal(self);
		
		if(sig) {
			switch(sig->type) {
			  case SIG_NEWPOS:
				sendSignal(&brain, sig);
				printNumber(sig->pos.n);
				updateBoard(&sig->pos);
				break;
			  case SIG_NEWMOVE:
				sendSignal(&brain, sig);
				moveDisk(&sig->mv);
				break;
			  case SIG_STATSUPDATE:
				updateStatistics(&sig->stats);
				break;
			  default:
				break;
			}
			
			destroySignal(sig);
		}
		
		c = getch();
		//c = wgetch(boardWin);
		switch(c) {
		  /* Quit. */
		  case 'q':
			send.type = SIG_END;
			sendSignal(&brain, &send);
			again = false;
			break;
		  /* Move the “cursor” (under the pegs). */
		  case KEY_LEFT:
			moveCursor((sel.cur==1) ? 3 : sel.cur-1);
			break;
		  case KEY_RIGHT:
			moveCursor(sel.cur%3 + 1);
			break;
		  case '1':
		  case '2':
		  case '3':
			moveCursor(c-'0');
			break;
		  /* Select/release a disk. */
		  case ' ':
			toggleSelected();
			break;
		  /* Shortcuts to move the cursor and select a disk. */
		  case '4':
		  case '5':
		  case '6':
			moveCursor(c-'3');
			toggleSelected();
			break;
		  /* Even shorter shortcuts to play a move directly. */
		  /* FIXME: When a disk is selected, it is ignored… */
		  /* FIXME: Some segfaults! */
		  case '7':
			attemptMove(1,2);    break;
		  case '8':
			attemptMove(1,3);    break;
		  case '9':
			attemptMove(2,3);    break;
		  /* Play the next move of the solution. */
		  /* FIXME: When a disk is selected, it is ignored… */
		  case 's':
			send.type = SIG_NEXTMOVE;
			sendSignal(&brain, &send);
			break;
		  case ERR:
		  default:
			break;
		}
	}
	
	endNumWin();
	endStatsWin();
	endBoardWin();
	endwin();
	
	pthread_exit(NULL);
}
