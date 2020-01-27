//daytimetcpsrv1.c
//Code by Lixin on 2020.01.27

#include "unp.h"
#include<time.h>

int main(int argc,char **argv)
{
	int listenfd,connfd;
	char buff[MAXLINE];
	socklen_t len;
	time_t ticks;
	struct sockaddr_storage cliaddr;

	if(argc!=2)
		err_quit("usgae:daytimetcpser1 <service/port#>");
	
	listenfd=tcp_listen(NULL,argv[1],NULL);

	for(;;){
		len=sizeof(cliaddr);
		connfd=accept(listenfd,(SA *)&cliaddr,&len);
		printf("connection from %s\n",sock_ntop((SA *)&cliaddr,len));

		ticks=time(NULL);
		snprintf(buff,sizeof(buff),"%.24s\r\n",ctime(&ticks));
		write(connfd,buff,strlen(buff));

		close(connfd);
	}
}
