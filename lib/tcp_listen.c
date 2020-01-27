//tcp_listen.c
//Code by Lixin on 2020.01.27

#include "unp.h"

int tcp_listen(const char *host,const char *serv,socklen_t *addrlenp)
{
	int listenfd,n;
	const int on=1;
	struct addrinfo hints,*res,*ressave;

	bzero(&hints,sizeof(struct addrinfo));
	hints.ai_flags=AI_PASSIVE;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;

	if((n=getaddrinfo(host,serv,&hints,&res))!=0)
		err_quit("tcp_listen error for %s,%s:%s",host,serv,gai_strerror(n));
	ressave=res;

	do{
		listenfd=socket(res->ai_family,res->ai_socktype,res->ai_protocol);
		if(listenfd<0)
			continue;
		setsockopt(listenfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
		if(bind(listenfd,res->ai_addr,res->ai_addrlen)==0)
			break;
		close(listenfd);
	}while((res=res->ai_next)!=NULL);
	
	if(res==NULL)
		err_sys("tcp_listen error for %s,%s",host,serv);

		listen(listenfd,LISTENQ);

		if(addrlenp)
			*addrlenp=res->ai_addrlen;

		freeaddrinfo(ressave);

		return (listenfd);
}
