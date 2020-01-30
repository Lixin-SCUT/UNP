//strclifork.c
//Code by Lixin on 2020.01.29

#include "unp.h"

void str_cli(FILE *fp,int sockfd){
	pid_t pid;
	char sendline[MAXLINE],recvline[MAXLINE];

	if((pid=fork())==0){
		while(readline(sockfd,recvline,MAXLINE)>0)
			fputs(recvline,stdout);

		kill(getppid(),SIGTERM);
		exit(0);
	}

	while(fgets(sendline,MAXLINE,fp)!=NULL)
		write(sockfd,sendline,strlen(sendline));

	shutdown(sockfd,SHUT_WR);
	pause();
	return;
}
