//connect_timeo.c
//Code by Lixin on 2020.01.28

#include "unp.h"

static void connect_alarm(int);

int connect_timeo(int sockfd,const SA *saptr, socklen_t salen,int nsec)
{
	sigfunc *sigfunc;
	int n;

	sigfunc= signal(SIGALRM,connect_alarm);
	if(alarm(nsec)!=0)
		err_msg("connect_timeo:alarm was already set");

	if((n=connect(sockfd,saptr,salen))<0){
		close(sockfd);
		if(errno==EINRTR)
			errno=ETIMEODOUT;
	}

	alarm(0);
	signal(SIGALRM,sigfunc);

	return n;
}

static void connect_alarm(int signo)
{
	return;
}
