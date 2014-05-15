/**
***  io.c
***
***    module:   io  −  source file
***    function: The interaction module (thread), which listen what the user do
***              and draw beautiful things onto the screen.
***    author:   Maëlan (aka Maëlan44)
***
**/

#include "io.h"





static void  initialPosition
  (Position* pos)
{
	pos->pos = DEFAULT_POS;
	pos->n =   gpos.n;
}



static void  randomPosition
  (Position* pos)
{
	static char buf[MAX_N];
	
	for(unsigned i = 0;  i < gpos.n;  i++)
		buf[i] = rand()%3 + 1;
	
	pos->pos = buf;
	pos->n =   gpos.n;
}



static void   manualPosition
  (Position* pos)
{
	static char posbuf[MAX_N];
	int c;
	
	pos->pos = posbuf;
	
	clearBoard();
	pos->n = gpos.n;
	
	nodelay(stdscr, false);
	for(unsigned i = pos->n;  i;  i--) {
		gpos.pegs[1][gpos.h[1]++] = i;
		unstackDisk(2);
		do
			c = getch();
		while(c < '1' || c > '3');
		pos->pos[pos->n-i] = c-'0';
		stackDisk(c-'0');
	}
	nodelay(stdscr, true);
}



static void  resetPosition
  (char mode)
{
	Signal sig;
	
	switch(mode) {
	  case 'i':
		initialPosition(&sig.pos);
		break;
	  case 'r':
		randomPosition(&sig.pos);
		break;
	  case 'm':
		manualPosition(&sig.pos);
		break;
	  default:
		break;
	}
	
	sig.type = SIG_NEWPOS;
	sendSignal(&brain, &sig);
	sendSignal(&io, &sig);
}



static void queryNextMove
  (void)
{
	Signal send;
	
	if(sel.n)
		cancelSelection();
	
	send.type = SIG_QUERYNEXTMOVE;
	sendSignal(&brain, &send);
}


static Thread  querySolutionThread;
static bool solutionRunning = false;

static void*  querySolutionProc
  (void* self)
{
	solutionRunning = true;
	
	while(1) {
		queryNextMove();
		usleep(800000LL);
	}
	
	solutionRunning = false;
	pthread_exit(NULL);
}



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
	init_pair(20, COLOR_BLACK,  -1);    /* color for drawings (N and pegs) */
	refresh();
	
	/* Windows. */
	initNumWin();
	initStatsWin();
	initBoardWin();
	
	again = true;
	while(again) {
		usleep(10000);    /* Mercy for our CPU! */
		
		while( (sig = getSignal(self)) ) {
			switch(sig->type) {
			  case SIG_NEWPOS:
				sendSignal(&brain, sig);
				updateNumber(sig->pos.n);
				updateBoard(&sig->pos);
				break;
			  case SIG_NEWMOVE:
				sendSignal(&brain, sig);
				moveDisk(&sig->mv);
				break;
			  case SIG_STATSUPDATE:
				updateStatistics(&sig->stats);
				break;
			  case SIG_SOLUTIONEND:
				endThread(&querySolutionThread);
				solutionRunning = false;
			  default:
				break;
			}
			
			destroySignal(sig);
		}
		
		c = getch();
		switch(c) {
		  
		  /* Quit. */
		  case 'q':
			send.type = SIG_END;
			sendSignal(&brain, &send);
			again = false;
			break;
		  
		  /* Initial, random or manual position. */
		  case 'i':
		  case 'r':
		  case 'm':
			resetPosition(c);
			break;
		  /* Changing N. */
		  case '-':
		  case '+':
			gpos.n += (c == '+') ? +1 : -1;
			if(gpos.n < 1)
				gpos.n = 1;
			else if(gpos.n > MAX_N)
				gpos.n = MAX_N;
			else
				resetPosition('i');
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
		  case '7':
			attemptMove(1,2);    break;
		  case '8':
			attemptMove(1,3);    break;
		  case '9':
			attemptMove(2,3);    break;
		  
		  /* Play the next move of the solution, or the entire solution. */
		  case 's':
			queryNextMove();
			break;
		  case 'S':
			/*send.type = SIG_QUERYSOLUTION;
			sendSignal(&brain, &send);*/
			if(!solutionRunning)
				startThread(&querySolutionThread, querySolutionProc);
			else {
				endThread(&querySolutionThread);
				solutionRunning = false;
			}
		  
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
