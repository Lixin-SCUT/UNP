//str_echo08.c
//Code by Lixin on 2020/01/14

#include "unp.h"

void
str_echo(int sockfd){
	long arg1,arg2;
	ssize_t n;
	char line[MAXLINE];
	for(;;){
		if((n=readline(sockfd,line,MAXLINE))==0)
			return;
		if(sscanf(line,"%ld%ld",&arg1,&arg2)==2)
			snprintf(line,sizeof(line),"%ld\n",arg1+arg2);
		n=strlen(line);
		writen(sockfd,line,n);
	}
}
