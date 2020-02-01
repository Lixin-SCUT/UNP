//serv06.c
//Code by Lixin on 2020.02.01

#include "unpthread.h"

int main(int argc,char **argv)
{
	int listenfd,connfd;
	void sig_int(int);
	void* doit(void*);
	pthread_t tid;
	socklen_t addrlen,clilen;
	struct sockaddr *cliaddr;

	if(argc==2)
		listenfd=tcp_listen(NULL,argv[1],&addrlen);
	else if(argc==3)
		listenfd=tcp_listen(argv[1],argv[2],&addrlen);
	else
		err_quit("usage:serv06 [<host>] <port#>");
	cliaddr=malloc(addrlen);
	
	signal(SIGINT,sig_int);

	for(;;){
		clilen=addrlen;
		connfd=accept(listenfd,cliaddr,&clilen);
		pthread_create(&tid,NULL,&doit,(void*)connfd);
	}
}

void* doit(void *arg)
{
	void web_child(int);
	pthread_detach(pthread_self());
	web_child((int)arg);
	close((int)arg);
	return NULL;
}
