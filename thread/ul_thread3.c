/*
 * 简单多线程程序
 */

#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

int main()
{
	pthread_t s1, s2;
	void *print_m(void *);
	struct timeval tv;
	int startsec, endsec;
	long starttime, endtime;
	gettimeofday(&tv, NULL);
	startsec = tv.tv_sec;
	starttime = tv.tv_usec;
	pthread_create(&s1, NULL, print_m, (void *)"Hi, ");
	pthread_create(&s2, NULL, print_m, (void *)"Wang\n");
	pthread_join(s1, NULL);
	pthread_join(s2, NULL);
	gettimeofday(&tv, NULL);
	endsec = tv.tv_sec;
	endtime = tv.tv_usec;
	printf("Running time: %d s %u us.\n", endsec - startsec, endtime - starttime);
}

void *print_m(void *m)
{
	int i;
	for(i = 0; i < 5; i++) {
		printf("%s", m);
		fflush(stdout);
		sleep(1);
	}
}
