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
	
	startThread(&brain, brainProc);
	startThread(&io, ioProc);
	
	sig.type = SIG_NEWPOS;
	sig.pos = (Position){ 4, "\1\1\3\1" };
	sendSignal(&brain, &sig);
	
	sig.type = SIG_NEWMOVE;
	sig.mv = (Move){ 3, 2 };
	sendSignal(&brain, &sig);
	sig.mv = (Move){ 2, 3 };
	sendSignal(&brain, &sig);
	sig.mv = (Move){ 1, 2 };
	sendSignal(&brain, &sig);
	sig.mv = (Move){ 2, 3 };
	sendSignal(&brain, &sig);
	
	sig.type = SIG_END;
	sendSignal(&brain, &sig);
	
	waitThread(&brain);
	waitThread(&io);
	return 0;
}
