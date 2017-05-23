/*
 * 无名管道 pipe
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
	int pid1, pid2, fd[2];
	char buf[50], s[50];
	pipe(fd);
	pid1 = fork();
	switch(pid1) {
		case -1:
			perror("fork failed");
			exit(1);
		case 0:
			lockf(fd[1], 1, 0);
			sprintf(buf, "child p1 is sending messages!\n");
			write(fd[1], buf, 50);
			sleep(5);
			lockf(fd[1], 0, 0);
			exit(0);
		default:
			pid2 = fork();
			switch(pid2) {
				case -1:
					perror("fork failed");
					exit(1);
				case 0:
					lockf(fd[1], 1, 0);
					sprintf(buf, "child p2 is sending messages!\n");
					write(fd[1], buf, 50);
					sleep(5);
					lockf(fd[1], 0, 0);
					exit(0);
				default:
					wait(NULL);
					read(fd[0], s, 50);
					printf("%s", s);
					wait(NULL);
					read(fd[0], s, 50);
					printf("%s", s);
					exit(0);
			}
	}
	
	close(fd[0]);
	close(fd[1]);
}
