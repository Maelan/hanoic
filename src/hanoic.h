/**
***  hanoic.h
***
***    module:   hanoic  −  header file
***    function: The main program.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#ifndef INCLUDED_HANOIC_2012_08_20_19_31_MM
#define INCLUDED_HANOIC_2012_08_20_19_31_MM



#include "datas.h"
#include "threads.h"
#include "brain.h"    /* That’s better. */
#include "io.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>





extern Thread  brain, io;





int  main
  (int ac, char** av);



#endif    /* header not included */
