/*
 * fork ·µ»ØÖµ
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int ret, mypid;
	mypid = getpid();
	printf("Before fork: pid = %d\n", mypid);

	ret = fork();
	if(ret < 0)
		printf("error in fork!\n");
	else if(ret == 0)
		printf("After fork: I'm the child process, ID is %d\n", getpid());
	else
		printf("After fork: I'm the parent process, ID is %d\n", getpid());

	return 0;
}
