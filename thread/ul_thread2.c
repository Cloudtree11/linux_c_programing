/*
 * 简单多进程程序 - 用于和多线程对比
 */

#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	void print_m(char *);
	pid_t pid1, pid2;
	struct timeval tv;
	int startsec, endsec;
	long starttime, endtime;
	
	gettimeofday(&tv, NULL);
	startsec = tv.tv_sec;
	starttime = tv.tv_usec;

	if((pid1 = fork()) < 0) {
		printf("fork1 failed!\n");
		exit(1);
	} else if (pid1 == 0) {
		print_m("Hi,");
		exit(0);
	} else if((pid2 = fork()) < 0) {
		printf("fork2 failed!\n");
		exit(1);
	} else if(pid2 == 0) {
		print_m("Cloud\n");
		exit(0);
	}

	wait();
	wait();
	gettimeofday(&tv, NULL);
	endsec = tv.tv_sec;
	endtime = tv.tv_usec;
	printf("Running time: %d s %u us.\n", endsec - startsec, endtime - starttime);
}

void print_m(char *m)
{
	int i;
	for(i = 0; i < 5; i++) {
		printf("%s", m);
		fflush(stdout);
		sleep(1);
	}
}


