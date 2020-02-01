//pthread08.c
//Code by Lixin on 2020.02.01

#include "unpthread.h"
#include "pthread08.h"

void thread_make(int i)
{
	void *thread_main(void*);

	pthread_create(&tptr[i].thread_tid,NULL,&thread_main,(void*)i);
	return;
}

void* thread_main(void *arg)
{
	int connfd;
	void web_child(int);

	pritf("thread %d starting\n",(int)arg);
	for(;;){
		pthread_mutex_lock(&child_mutex);
		while(iget==iput)
			pthread_cond_wait(&child_cond,&child_mutex);
		connfd=clifd[iget];
		if(++iget==MAXNCLI)
			iget=0;
		pthread_mutex_unlock(&clifd_mutex);
		tptr[(int)arg].thread_count++;

		web_child(connfd);
		close(fd);
	}
}
