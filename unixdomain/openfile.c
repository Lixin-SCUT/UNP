//opnefile.c
//Code by Lixin on 2020.01.28

#include "unp.h"

int main(int argc,char **argv)
{
	int fd;

	if(argc!=4)
		err_quit("openfine <sockfd#><filename><mode>");
	
	if((fd=open(argv[2],atoi(argv[3])))<0)
		exit((errno>0)?errno:255);
	
	if(write_fd(atoi(argv[1]),"",1,fd)<0)
		exit((errno>0)?errno:255);

	exit(0);
}
