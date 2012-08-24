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





int  main
  (int ac, char** av)
{
	Signal sig;
	
	sig.type = SIG_NEWPOS;
	
	/* Parse the position format passed via the command-line. */
	if(ac > 1) {
		unsigned i;
		for(i = 0;  av[1][i];  i++) {
			if(i > MAX_N) {
				fprintf(stderr, "Error: too many disks (max. %u).\n", MAX_N);
				return EXIT_FAILURE;
			}
			else if(av[1][i] < '1'  ||  av[1][i] > '3') {
				fprintf(stderr,
				  "Error: incorrect position format. This must be a sequence of"
				  " digits from 1 to 3 exclusively.\n");
				return EXIT_FAILURE;
			}
			else
				av[1][i] -= '0';
		}
		sig.pos.n =   i;
		sig.pos.pos = av[1];
	}
	else {
		sig.pos.n =   DEFAULT_N;
		sig.pos.pos = DEFAULT_POS;
	}
		
	/* Start the game. */
	startThread(&brain, brainProc);
	startThread(&io, ioProc);
	
	/* Init the position. */
	sendSignal(&brain, &sig);
	
	/* End. */
	waitThread(&brain);
	waitThread(&io);
	return EXIT_SUCCESS;
}
