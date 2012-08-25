/**
***  hanoic.c
***
***    module:   hanoic  −  source file
***    function: The main program.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#include "hanoic.h"





Thread  brain, io;





static unsigned  s2ui
  (char const* s)
{
	unsigned n;
	
	for(n = 0;  *s;  s++) {
		if(*s < '0'  ||  *s > '9')
			return UINT_MAX;
		n = 10*n + *s-'0';
	}
	
	return n;
}



int  main
  (int ac, char** av)
{
	Signal sig;
	
	srand(time(NULL));
	
	sig.type = SIG_NEWPOS;
	
	/* Parse the position format passed via the command-line. */
	if(ac > 1) {
		if(av[1][0] == '-') {
			sig.pos.n =   s2ui(av[1]+1);
			sig.pos.pos = DEFAULT_POS;
			if(sig.pos.n == UINT_MAX)
				goto ErrIncorrectN;
		}
		else {
			unsigned i;
			for(i = 0;  av[1][i];  i++) {
				if(av[1][i] < '1'  ||  av[1][i] > '3')
					goto ErrIncorrectPos;
				av[1][i] -= '0';
			}
			sig.pos.n =   i;
			sig.pos.pos = av[1];
		}
		if(sig.pos.n > MAX_N)
			goto ErrTooManyDisks;
	}
	else {
		sig.pos.n =   DEFAULT_N;
		sig.pos.pos = DEFAULT_POS;
	}
		
	/* Start the game. */
	startThread(&brain, brainProc);
	startThread(&io, ioProc);
	
	/* Init the position. */
	sendSignal(&io, &sig);
	
	/* End. */
	waitThread(&brain);
	waitThread(&io);
	return EXIT_SUCCESS;

	if(0)
	  ErrTooManyDisks:
		fprintf(stderr, "Error: too many disks (max. %u).\n", MAX_N);
	if(0)
	  ErrIncorrectN:
		fprintf(stderr, "Error: incorrect number of disks.\n");
	if(0)
	  ErrIncorrectPos:
		fprintf(stderr,
		  "Error: incorrect position format. This must be a sequence of"
		  " digits from 1 to 3 exclusively.\n");
	
	return EXIT_FAILURE;

}
