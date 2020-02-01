//serv01.c
//Code by Lixin on 2020.01.31

#include "unp.h"

int main(int argc,char **argv)
{
	int listenfd,connfd;
	pid_t pid;
	void sig_chld(int),sig_int(int),web_child(int);
	socklen_t clilen,addrlen;
	struct sockaddr *cliaddr;

	if(argc==2)
		listenfd=tcp_listen(NULL,argv[1],&addrlen);
	else if(argc==3)
		listenfd=tcp_listen(argv[1],argv[2],&addrlen);
	else
		err_quit("usage:serv01 [<host>] <potr#>");
	cliaddr=malloc(addrlen);

	signal(SIGCHLD,sig_chld);
	signal(SIGINT,sig_int);

	for(;;){
		clilen=addrlen;
		if((connfd=accept(listenfd,cliaddr,&clilen))<0){
			if(errno=EINTR)
				continue;
			else
			 err_sys("accept errpr");
		}

		if((childpid=fork())==0){
			close(listenfd);
			web_child(connfd);
			eixt(0);
		}
		close(connfd);
	}
}

void sig_int(int signo){
	void pr_cpu_time(void);

	pr_cpu_time();
	exit(0);
}


