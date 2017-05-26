/*
 * 线程互斥量
 */

#include <stdio.h>
#include <pthread.h>

#define NUM 5
int counter = 0;

pthread_mutex_t counter_lock = PTHREAD_MUTEX_INITIALIZER;

int main()
{
	pthread_t t1, t2;
	void *print_c(void *);
	void *counter2(void *);
	int i;
	pthread_create(&t1, NULL, print_c, NULL);
	pthread_create(&t2, NULL, counter2, NULL);
	
	for(i = 0; i < NUM; i++) {
		pthread_mutex_lock(&counter_lock);
		counter++;
		sleep(1);
		pthread_mutex_unlock(&counter_lock);
	}

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
}

void *print_c(void *m)
{
	int i;
	for(i = 0; i < NUM; i++) {
		printf("counter = %d\n", counter);
		sleep(1);
	}
	return 0;
}

void *counter2(void *m)
{
	int i;
	while(1) {
		if(counter < 0) break;
		pthread_mutex_lock(&counter_lock);
		counter--;
		pthread_mutex_unlock(&counter_lock);
	}
	return 0;
}
