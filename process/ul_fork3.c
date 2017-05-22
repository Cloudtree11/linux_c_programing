/*
 * 子进程再去 fork
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("This is my pid: %d\n", getpid());
	fork();
	fork();
	fork();
	printf("now, my pid: %d\n", getpid());
}


