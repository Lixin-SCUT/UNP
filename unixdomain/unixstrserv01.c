//unixstrserv01.c
//Code by Lixin on 2020.01.28

int main(int argc,char **argv)
{
	int listenfd,connfd;
	pid_t childpid;
	socklen_t clilen;
	struct sockaddr_un cliaddr,servaddr;
	void sig_chld(int);

	listenfd=socket(AF_LOCAL,SOCK_STREAM,0);

	unlink(argv[1]);
	bzero(&servaddr,sizeof(servaddr));
	servaddr.sun_family=AF_LOCAL;
	strcpy(servaddr.sun_path,UNIXSTR_PATH);

	bind(listenfd,(SA *)&servaddr,sizeof(servaddr));

	listen(listenfd,LISTENQ);

	signal(SIGCHLD,sig_chld);

	for(;;){
		chilen=sizeof(cliaddr);
		if((connfd=accept(listenfd,(SA *)&cliaddr,&clilen))<0){
			if(errno==EINTR)
				continue;
			else
				err_sys("accept error");
		}
		if((childpid=fork())==0){
			close(listenfd);
			str_echo(connfd);
			exit(0);
		}
		close(connfd);
	}
}
