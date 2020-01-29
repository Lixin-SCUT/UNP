//mycat.c
//Code by Lixin on 2020.01.28

#include "unp.h"

int my_open(const char *,int);

int main(int argc,char **argv)
{
	int fd,n;
	char buff[BUFFSIZE];

	if(argc!=2)
		err_quit("usage:mycat <pathname>");

	if((fd=my_open(argv[1],O_RDONLY))<0)
		err_sys("cannot open %s",argv[1]);
	while((n=read(fd,buff,BUFSIZE))>0)
		write(STDOUT_FILENO,buff,n);
	exit(0);
}
