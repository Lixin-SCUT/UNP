//checkopts.c
//Code by Lixin on 2020.01.17

#inlcude "unp.h"
#include <netinet/tcp.h>

union val{
	int i_val;
	long l_val;
	struct linger linger_val;
	struct timeval timeval_val;
}val;

struct sock_opts{
	const char *opt_str;
	int opt_level;
	int opt_name;
	char *(*opt_val_str)(union val *,int);
}sock_opts[]={
	{"SO_KEEAPALIVE",SOL_SOCKET,SO_KEEPALIVE,sock_str_flag},
	{NULL,0,0,NULL}
}

int main(int argc,char **argv)
{
	int fd;
	socklen_t, len;
	struct sock_opts *ptr;

	for(ptr=socl_opts;ptr->opt_str!=NULL;ptr++){
		printf("%s:",ptr->opt_str);
		if(ptr->opt_val_str==NULL)
			printf("(undefined)\n");
		else{
			switch(ptr->opt_level){
				case SOL_SOCKET:
				case IPPROTO_IP:
				case IPPROTO_TCP:
					fd=socket(AF_INET,SOCK_STREAM,0);
					break;
				default:
					perror("cannot creat fd for level %d\n",ptr->opt_level);
			}

			len=sizeof(val);
			if(getsockopt(fd,ptr->opt_level,ptr->opt_name,&val,&len)==-1){
				perror("getsockopt error");
			}else{
				printf("default = %s\n",(*ptr->opt_val_str)(&val,len));
			}
			close(fd);
		}
	}
	exit(0);
}
