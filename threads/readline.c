//readline.c
//Code by Lixin on 2020.01.30

#include "unpthreads.h"

static pthread_key_t r1_key;
static pthread_once_t r1_once=PTHREAD_ONCE_INIT;

static void readline_destructor(void *ptr)
{
	free(ptr);
}

static void readline_once(void)
{
	pthread_key_create(&r1_key,readline_destructor);
}

typedef struct{
	int r1_cnt;
	char *r1_bufptr;
	char r1_buf[MAXLINE];
}Rline;

staic ssize_t my_read(Rline *tsd,int fd,char *ptr)
{
	if(tsd->r1_cnt<=0){
		agian:
		if((tsd->r1_cnt=read(fd,tsd->r1_buf,MAXLINE))<0){
			if(errno==EINTR)
				goto again;
			return -1;
		}else if(tsd->r1_cnt==0)
			return 0;
		tsd->re_bufptr=tsd->r1_buf;
	}

	--tsd->r1_cnt;
	*ptr=*tsd->bufptr++;
	return 1;
}

ssize_t readline(int fd,void *vptr,size_t maxlen)
{
	size_t n,rc;
	char c,*ptr;
	Rline *tsd;

	pthread_once(&r1_once,readline_once);
	if((tsd=pthread_getspecific(r1_key))==NULL){
		tsd=calloc(1,sizeof(Rline));
		pthread_setspecific(r1_key,tsd);
	}

	ptr=vptr;
	for(n=1;n<maxlen;++n){
		if((rc=my_read(tsd,fd,&c))==1){
			*ptr++=c;
			if(c=='\n')
				break;
		}else if(rc==0){
			*ptr=0;
			return n-1;
		}else
			return -1;
	}
	*ptr=0;
	return n;
}
