/**
***  threads.h
***
***    module:   threads  −  header file
***    function: Threads management.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#ifndef INCLUDED_HANOIC_THREADS_2012_08_20_19_31_MM
#define INCLUDED_HANOIC_THREADS_2012_08_20_19_31_MM

#include "datas.h"
#include <pthread.h>
#include <stdio.h>     /* perror */
#include <stdlib.h>    /* malloc/free */





typedef enum {
	SIG_END,
	SIG_NEWPOS,
	SIG_NEWMOVE,
	SIG_NEXTMOVE,
	SIG_INFOUPDATE,
	SIG_LAST
} SignalType;



typedef struct Signal {
	struct Signal* next;
	SignalType type;
	union {
		Position pos;
		Move mv;
	} ;
} Signal;



typedef struct {
	Signal *first, *last;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
} SignalQueue;



typedef  void* (*Procedure)(void*);



typedef struct {
	pthread_t th;
	SignalQueue sigq;
	Procedure proc;
} Thread;





void  startThread
  (Thread*, Procedure);



void  waitThread
  (Thread*);



void  endThread
  (Thread*);



void  destroyThread
  (Thread*);



Signal*  getSignal
  (Thread*);



Signal*  waitSignal
  (Thread*);



void  sendSignal
  (Thread*, Signal const*);



void  destroySignal
  (Signal*);



#endif    /* header not included */
