
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



/* A move (ie. moving a disk from one peg to another). */
typedef struct Move {
	char src, dest;     /* the source and destination pegs (numbers from 1 to 3) */
	//unsigned char n;    /* the number of the disk to be moved */
} Move;



/* A position. */
typedef struct {
	unsigned n;         /* number of disks */
	char const* pos;    /* array of numbers from 1 to 3 describing the position */
} Position;



/* Statistics about the game. */
typedef struct {
	unsigned initial,    /* optimal number of moves at the beginning */
	         fromNow,    /* optimal number of moves from now */
	         done,       /* moves played since the beginning */
	         errors;     /* “bad” moves (ie. not the expected ones) played */
} Statistics;



#endif    /* header not included */
