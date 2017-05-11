
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;
void ding(int sig)
{
	alarm_fired = 1;
}

int main()
{
	pid_t pid;
	printf("alarm application starting\n");

	pid = fork();
	switch(pid) {
		case -1:
			/* Failure */
			perror("fork failed");
			exit(1);
		case 0:
			/* child */
			sleep(5);
			kill(getppid(), SIGALRM); /* kill 发送信号给父进程 */
			exit(0);
	}

	/* If we get here we are the parent process */
	printf("waiting for alarm to go off\n");
	(void)signal(SIGALRM, ding);

	pause(); /* 把程序的执行挂起直到有一个信号出现为止 */
	if(alarm_fired)
		printf("Ding!\n");

	printf("done\n");
	exit(0);
}




