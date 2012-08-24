/**
***  threads.c
***
***    module:   threads  −  source file
***    function: Threads management.
***    author:   Maëlan (aka Maëlan44)
***              (see < http://www.siteduzero.com/membres-294-232877.html >)
***
**/

#include "threads.h"





void  startThread
  (Thread* thread, Procedure proc)
{
	thread->proc = proc;
	thread->sigq.first = thread->sigq.last = NULL;
	thread->sigq.mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	thread->sigq.cond = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
	pthread_create(&thread->th, NULL, proc, thread);
}



void  waitThread
  (Thread* thread)
{
	pthread_join(thread->th, NULL);
	destroyThread(thread);
}



void  endThread
  (Thread* thread)
{
	pthread_cancel(thread->th);
	destroyThread(thread);
}



void  destroyThread
  (Thread* thread)
{
	Signal *sig, *next;
	
	next = thread->sigq.first;
	while(next) {
		sig = next;
		next = next->next;
		free(sig);
	}
	thread->sigq.first = thread->sigq.last = NULL;
}



Signal*  getSignal
  (Thread* thread)
{
	Signal* sig;
	
	if(!thread->sigq.first)
		return NULL;
	
	pthread_mutex_lock(&thread->sigq.mutex);
	
	sig = thread->sigq.first;
	thread->sigq.first = sig->next;
	if(!sig->next)
		thread->sigq.last = NULL;
	
	pthread_mutex_unlock(&thread->sigq.mutex);
	
	return sig;
}



Signal*  waitSignal
  (Thread* thread)
{
	Signal* sig;
	
	pthread_mutex_lock(&thread->sigq.mutex);
	
	if(!thread->sigq.first)
		pthread_cond_wait(&thread->sigq.cond, &thread->sigq.mutex);
	
	sig = thread->sigq.first;
	thread->sigq.first = sig->next;
	if(!sig->next)
		thread->sigq.last = NULL;
	
	pthread_mutex_unlock(&thread->sigq.mutex);
	
	return sig;
}



void  sendSignal
  (Thread* thread, Signal const* sig)
{
	Signal* sig2 = malloc(sizeof(*sig));
	if(!sig2) {
		perror("Memory (malloc) error");
		return;
	}
	*sig2 = *sig;
	sig2->next = NULL;
	
	pthread_mutex_lock(&thread->sigq.mutex);
	
	if(thread->sigq.last)
		thread->sigq.last->next = sig2;
	else
		thread->sigq.first = sig2;
	thread->sigq.last = sig2;
	
	if(thread->sigq.first == sig2)
		pthread_cond_signal(&thread->sigq.cond);
	
	pthread_mutex_unlock(&thread->sigq.mutex);
}



void  destroySignal
  (Signal* sig)
{
	free(sig);
}
