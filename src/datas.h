
/**
***  datas.h
***
***    module:   datas  −  header file
***    function: Type and constant definitions used by the other parts of the
***              program.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#ifndef INCLUDED_HANOIC_DATAS_2012_08_20_19_31_MM
#define INCLUDED_HANOIC_DATAS_2012_08_20_19_31_MM



#define  MAX_N        12
#define  DEFAULT_N     4
#define  DEFAULT_POS  "\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1\1"



typedef struct Move {
	char src, dest;
	//unsigned char n;
} Move;



typedef struct {
	unsigned n;
	char const* pos;
} Position;



/*§*/



#endif    /* header not included */
