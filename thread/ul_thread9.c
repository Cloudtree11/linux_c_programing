/*
 * 线程条件变量
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int gnum = 0;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread1(void *);
void *thread2(void *);

int main(void)
{
	pthread_t t1;
	pthread_t t2;
	
	pthread_create(&t1, NULL, thread1, (void *)NULL);
	pthread_create(&t2, NULL, thread2, (void *)NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	exit(0);
}

void *thread1(void *m)
{
	for(;;) {
		pthread_mutex_lock(&mutex);
		if(gnum % 3 == 0)
			/* 
			 * pthread_cond_signal - 用于将符合条件的信息以信号形式发送出去，
			 * 使得等待条件的线程队列的第一个线程收到此信号 
			 */
			pthread_cond_signal(&cond);
		else {
			printf("thread1: %d\n", gnum);
			gnum ++;
		}
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}

void *thread2(void *m)
{
	while(1) {
		pthread_mutex_lock(&mutex);
		if(gnum % 3 != 0)
			/* pthread_cond_wait - 使线程进入条件变量队列休眠 */
			pthread_cond_wait(&cond, &mutex);
		printf("thread2: %d\n", gnum);
		gnum ++;
		pthread_mutex_unlock(&mutex);
		sleep(1);
	}
}
