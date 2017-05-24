/*
 * 创建守护进程
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAXFILE 65535

int main()
{
	pid_t pc;
	int i, fd, len;
	char *buf = "This is a Dameon TEST!\n";

	len = strlen(buf);
	pc = fork();
	if(pc < 0) {
		printf("error fork\n");
		exit(1);
	} else if(pc > 0)
		exit(0);
	else {
		/* setsid - run a program in a new session */
		setsid();
		/* 改变当前目录为根目录（不继承父进程的当前工作目录）  */
		chdir("/");
		/* 重设文件权限掩码 */
		umask(0);
		/* 关闭文件描述符  */
		for(i = 0; i < MAXFILE; i++)
			close(i);
		while(1) {
			if(fd = open("/tmp/dameon.log", O_CREAT | O_WRONLY | O_APPEND, 0600) < 0){
				perror("open");
				exit(1);
			}
			write(fd, buf, len + 1);
			close(fd);
			sleep(10);
		}
	}
}
