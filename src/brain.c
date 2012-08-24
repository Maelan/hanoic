/**
***  brain.c
***
***    module:   brain  −  source file
***    function: The brain, i.e. the part (thread) which compute things.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#include "brain.h"





static MoveStack  moves = {
	.cur = MAX_MOVES
};





static void  addMove
  (int src, int dest/*, unsigned n*/)
{
	moves.cur--;
	moves.mv[moves.cur].src =  src;
	moves.mv[moves.cur].dest = dest;
	//moves.mv[moves.cur].n =    n;
}





static void  pullMove
  (void)
{
	moves.cur++;
}



/* Solves the Tower of Hanoi puzzle when all the n disks are on the ‘src’ peg
 * and must go to the ‘dest’. Acts as ‘solve’ described below, except that it
 * does not need a description of the initial position, only the source and
 * destination pegs. */
static unsigned  solveOrdered
  (unsigned n, int src, int dest)
{
	if(!n)
		return 0;
	
	/* 3) Move the n-1 tower on the destination peg. */
	solveOrdered(n-1, (6-src-dest), dest);
	/* 2) Move the disk n on the destination peg. */
	addMove(src, dest/*, n*/);
	/* 1) Move the n-1 tower on the intermediary peg. */
	solveOrdered(n-1, src, (6-src-dest) );
	
	return (1<<n) - 1;    // 2^n - 1
}



/* Solves the Tower of Hanoi puzzle, from any initial position, the optimal way.
 * Takes as argument the number of disks, and the position. The position is
 * described by an array of numbers from 1 to 3 (of type ‘char’), each number
 * indicating the peg on which the corresponding disk currently is; the first
 * number matchs the disk n, the second matchs the disk n-1, etc.
 * Store the moves in the moves stack, and returns the number of moves done. */
static unsigned  solve
  (unsigned n, char const* pos, int dest)
{
	/* base case: */
	if(!n)
		return 0;
	
	/* recursion: */
	if(*pos == dest)
		return solve(n-1, pos+1, dest);
	else {
		/* NOTE: All is done in reverse order, since we have to *stack* the
		   moves, the first being at the top. That’s why we need ‘solveOrdered’,
		   which does not need to remember the position (otherwise, we could
		   have used recursion for step 3 too). */
		unsigned r;
		/* 3) Move the n-1 tower on the destination peg. */
		solveOrdered(n-1, (6-*pos-dest), dest);
		/* 2) Move the disk n on the destination peg. */
		addMove(*pos, dest/*, n*/);
		/* 1) Regroup the n-1 tower on the intermediary peg. */
		r = solve(n-1, pos+1, (6-*pos-dest) );
		return r + (1<<(n-1));    // r + 2^(n-1)
	}
}



/*  */
static void  updateMoves
  (Move const* mv)
{
	if(moves.cur < MAX_MOVES  &&  mv->src == moves.mv[moves.cur].src) {
		if(mv->dest == moves.mv[moves.cur].dest)
			pullMove();
		else
			moves.mv[moves.cur].src = mv->dest;
	}
	else
		addMove(mv->dest, mv->src/*, mv->n*/);
}



void*  brainProc
  (void* self)
{
	Signal* sig;
	bool again;
	
	again = true;
	while(again) {
		sig = waitSignal(self);
		
		switch(sig->type) {
		  case SIG_END:
			again = false;
			break;
		  case SIG_NEWPOS:
			sendSignal(&io, sig);
			solve(sig->pos.n, sig->pos.pos, 3);
			break;
		  case SIG_NEWMOVE:
			updateMoves(&sig->mv);
			break;
		  default:
			break;
		}
		
		destroySignal(sig);
	}
	
	pthread_exit(NULL);
}
