//str_cli.c
//Code by Lixin on 2020/01/13

#include "unp.h"

void str_cli(FILE *fp,int sockfd)
{
	char sendline[MAXLINE],recvline[MAXLINE];

	while(fgets(sendline,MAXLINE,fp)!=NULL){
		writen(sockfd,sendline,strlen(sendline));
		if(readline(sockfd,recvline,MAXLINE)==0)
			err_quit("str_cli:server terminated prematurely");
		Fput(recvline,stdout);
	}
}
