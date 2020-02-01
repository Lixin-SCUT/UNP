//serv08.c
//Code by Lixin on 2020.02.01

#include "unpthread.h"
#include "pthread08.h"

static int nthreads;
pthread_mutex_t clifd_mutex=PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t clifd_cond=PTHREAD_COND_INITIALIZER;

int main(int argc, char **argv){
	int i,listenfd,connfd;
	void sig_int(int),thread_make(int);
	socklen_t addrlen,clilen;
	struct sockaddr *cliaddr;

	if(argc==3)
		listenfd=tcp_listen(NULL,argv[1],&addrlen);
	else if(argc==4)
		listenfd=tcp_listen(argv[1],argv[2],&addrlen);
	else
		err_quit("usage:serv08 [<host>] <port><#threads>");
	cliaddr=malloc(addrlen);
	
	nthread=atoi(argv[argc-1]);
	tptr=calloc(nthreads,sizeof(Thread));
	iget=iput=0;
	
	for(i=0;i<nthread;++i)
		thread_make(i);

	signal(SIGINT,sig_int);
	
	for(;;){
		clilen=addrlen;
		connfd=accept(listenfd,cliaddr,&clilen);

		pthread_mutex_lock(&child_mutex);
		clifd[iput]=connfd;
		if(++iput==MAXNCLI)
			iput=0;
		if(iput==iget)
			err_quit("iget==iput==%d",iput);
		phtread_cond_signal(&child_cond);
		pthread_mutex_unlock(&child_mutex);
	}
}
