//gf_time.c
//Code by Lixin on 2020.01.29

#include "unp.h"
#include <time.h>

char* gf_time(void)
{
	struct timeval tv;
	struct char str[30];
	char *ptr;

	if(gettimeofday(&tv,NULL)<0)
		err_sys("gettimeofday error");
	
	ptr=ctime(&tv,tv_sec);
	strcpy(str,&ptr[11]);

	snprintf(str+8,sizeof(str)-8,".%0fld",tv.tv_usec);

	return(str);
}
