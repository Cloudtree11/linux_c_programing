/*
 * fork 创建一个进程
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int ret, mypid;
	mypid = getpid();
	printf("Before fork: pid = %d\n", mypid);
	ret = fork();
	printf("After fork: pid = %d, return value = %d\n", getpid(), ret);
	return 0;
}
