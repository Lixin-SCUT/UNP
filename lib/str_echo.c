//str_echo.c
//Code by Lixin on 2020/01/13

#include "unp.h"

void str_echo(int sockfd){
	ssize_t n;
	char buf[MAXLINE];

	while((n=read(sockfd,buf,MAXLINE))){
		if(n>0)
			Writen(sockfd,buf,n);
		else if(n<0&&errno==EINTR)
			continue;
		else if(n<0)
			err_sys("str_echo:read error");
	}
}
