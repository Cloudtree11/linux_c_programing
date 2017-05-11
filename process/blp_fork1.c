
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	char *message;
	int n;

	printf("fork program starting\n");
	pid = fork(); //子进程的 fork 返回 0
	switch(pid)
	{
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			message = "This is the child";
			n = 5;
			break;
		default:
			message = "This is the partent";
			n = 3;
			break;
	}

	for(; n > 0; n--) {
		puts(message);
		sleep(1);
	}
	exit(0);
}






