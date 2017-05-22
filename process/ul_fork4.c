/*
 * vfork
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("This is my pid: %d\n", getpid());
	/*
	 * fork 直接共享父进程的虚拟空间，并且保证子进程先运行，
	 * 在它调用exec或exit之后父进程才可能被调度运行
	 */
	vfork();
	vfork();
	vfork();
	printf("now, my pid: %d\n", getpid());
	exit(0);
}


