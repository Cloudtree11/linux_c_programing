
#include <stdlib.h>
#include <stdio.h>

/*
 * 程序必须等待由system程序启动的进程结束后才能继续，无法立刻执行其他任务
 */

int main()
{
	printf("Running ps with system\n");
	system("ps ax");
	printf("Done.\n");
	exit(0);
}
