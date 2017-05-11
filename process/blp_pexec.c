
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * exec函数可以把当前进程替换为一个新进程，将程序的执行从一个程序切换为另一个程序。
 * 在新的程序执行后，原来的程序就不再运行了。
 */


int main()
{
	printf("Running ps with execlp\n");
	execlp("ps", "ps", "ax", 0);
	printf("Done.\n");
	exit(0);
}

