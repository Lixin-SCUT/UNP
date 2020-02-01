//serv02.c
//Code by Lixin on 2020.01.31

#include "unp.h"

static int nchildren;
static pid_t *pids;

int main(int argc,char **argv)
{
	int listenfd,i;
	void sig_int(int);
	socklen_t addrlen;
	pid_t child_make(int,int,int);

	if(argc==3)
		listenfd=tcp_listen(NULL,argv[1],&addrlen);
	else if(argc==4)
		listenfd=tcp_listen(argv[1],argv[2],&addrlen);
	else
		err_quit("usage:serv02 [<host>] <potr#><children#>");
	nchildren=atoi(argv[argc-1]);
	pids=calloc(nchildren,sizeof(pid_t));

	for(i=0;i<nchildren;++i)
		pids[i]=child_make(i,listenfd,addrlen);

	signal(SIGINT,sig_int);

	for(;;){
		pause();
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
	int i;

	for(i=0;i<nchildren;++i)
		kill(pids[i],SIGTERM);
	while(wait(NULL)>0)
		;
	if(errno!=ECHILD)
		err_sys("wait error");
	
	pr_cpu_time();
	exit(0);
}

