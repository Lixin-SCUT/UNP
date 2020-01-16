//strcliselect01.c
//Code by Lixin on 2020.01.16

#include "unp.h"

void
str_cli(FILE *fp,int sockfd)
{
	int maxfdp1;
	fd_set rset;
	char sendline[MAXLINE],recvline[MAXLINE];

	FD_ZERO(&rset);
	for(;;){
		FD_SET(fileno(fp),&rset);
		FD_SET(sockfd,&rset);
		maxfdp1=max(fileno(fp),sockfd)+1;
		select(maxfdp1,&rset,NULL,NULL,NULL);

		if(FD_ISSET(sockfd,&rset))
			if(readline(sockfd,recvline,MAXLINE)==0)
				err_quit("str_cli:server terminated prematurely");
			fputs(recvline,stdout);

		if(FD_ISSET(fileno(fp),&rset))
			if(fgets(sendline,MAXLINE,fp)==NULL)
				return;
			write(sockfd,sendline,strlen(sendline));
	}
}
