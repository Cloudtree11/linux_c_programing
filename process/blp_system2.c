
#include <stdlib.h>
#include <stdio.h>

/*
 * 使用system函数远非启动其他进程的理想手段，因为它必须用一个shell来启动需要的程序，
 * 效率不高
 */

int main()
{
	printf("Running ps with system\n");
	system("ps ax &");
	printf("Done.\n");
	exit(0);
}
