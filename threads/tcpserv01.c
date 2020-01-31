//tcpserv01.c
//Code by Lixin on 2020.01.30

#include "unpthread.h"

static void* doit(void*);

int main(int argc,char **argv)
{
	int listenfd,connfd;
	pthread_t tid;
	socklen_t addrlen,len;
	struct sockaddr *cliaddr;

	if(argc==2)
		listenfd=tcp_listen(NULL,argv[1],&addrlen);
	else if(argc==3)
		listenfd=tcp_listen(argv[1],argv[2],&addrlen);
	else
		err_quit("usage:tcpserv-1[<host>]<service or port>");
	cliaddr=Malloc(addrlen);

	for(;;){
		len=addrlen;
		connfd=accept(listenfd,cliaddr,&len);
		pthread_create(&tid,NULL,&doit,(void*)connfd);
	}
}

static void* doit(void *arg)
{
	pthread_detach(pthread_self());
	str_echo((int)arg);
	close((int)arg);
	return NULL;
}
