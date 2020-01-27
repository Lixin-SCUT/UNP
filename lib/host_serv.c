//host_serv.c
//Code by Lixin on 2020.01.27

#include "unp.h"

struct addrinfo* host_serv(const char *host,const char *serv,int family,int socktype)
{
	int n;
	struct addrinfo hints,*res;

	bzero(&hints,sizeof(strcut addrinfo));
	hints.ai_flags=AI_CANONNAME;
	hints.ai_family=AF_INET;
	hints.ai_socktype=socktype;
	
	if((n=getaddrinfo(host,serv,hints,&res))!=0)
		return(NULL);

	return(res);
}
