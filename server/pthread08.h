//pthread08.h
//Code by Lixin on 2020.02.01

typedef struct{
	pthread_t thread_tid;
	long thread_count;
}Thread;
Thread *tptr;

#define MAXNCLI 32
int clifd[MAXNCLI],iget,iput;
pthread_mutex_t clifd_mutex;
pthread_cond_t clifd_cond;
