//sigchldwaitpid.c
//Code by Lixin on 2020/01/14

#include "unp.h"

void
sig_chld(int signo){
	pid_t pid;
	int stat;
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
		printf("child %d terminated\n",pid);
	return;
}
