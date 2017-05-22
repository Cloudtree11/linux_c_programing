/*
 * 父子进程之间的同步 - wait
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int i,pid;
	void child_pro(), parent_pro();
	i = getpid();
	printf("Before fork: mypid = %d\n", i);
	if((pid  = fork()) < 0)
		printf("fork failed!\n");
	else if(pid == 0)
		child_pro();
	else
		parent_pro(i);
}

void child_pro()
{
	printf("This is child process, pid = %d, and will sleep for 2 seconds\n",
			getpid());
	sleep(2);
	printf("child done! Exit, now!\n");
	exit(10);
}

void parent_pro(int ppid)
{
	int k, status;
	/*
	 * wait - suspends execution of the calling process until one of its children terminates
	 */
	k = wait(&status);
	printf("This is parent process, pid = %d, wait return = %d, wait status = %d\n",
			ppid, k, status);
}
