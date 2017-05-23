/*
 * 有名管道 - fifo 写管道程序
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MYFIFO "/tmp/myfifo"
#define MAX_BUFFER_SIZE PIPE_BUF

int main(int argc, char * argv[])
{
	int fd;
	char buff[MAX_BUFFER_SIZE];
	int nwrite;

	if(argc <= 1) {
		printf("Usage: ./fifo_wr string\n");
		exit(1);
	}

	sscanf(argv[1], "%s", buff);
	fd = open(MYFIFO, O_WRONLY);
	if(fd == -1) {
		printf("Open fifo file failed\n");
		exit(1);
	}
	if((nwrite = write(fd, buff, MAX_BUFFER_SIZE)) > 0) {
		printf("Write %s to FIFO\n", buff);
	}
	close(fd);
	exit(0);
}
