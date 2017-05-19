/*
 * select 系统调用
 */

#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	char buffer[128];
	int result, nread;

	fd_set inputs, testfds;
	struct timeval timeout;

	/*
	 * FD_ZERO - clears a set
	 * FD_SET/FD_CLR - add or remove a given file descriptor from a set.
	 * 将 stdin（0）加入到描述符集合中
	 */
	FD_ZERO(&inputs);
	FD_SET(0, &inputs);

	while(1) {
		testfds = inputs;
		timeout.tv_sec = 2;
		timeout.tv_usec = 500000;

		/*
		 * int select(int nfds, fd_set *readfds, fd_set *writefds,
		 *                   fd_set *exceptfds, struct timeval *timeout)
		 * Allow a program to  monitor  multiple  file  descriptors, waiting  until one or more of the file descriptors become "ready" for some class of I/O operation (e.g., input possible).
		 * nfds - the highest-numbered file descriptor in any of the three sets
		 * readfds - 可读描述符集合
		 * writefds - 可写描述符集合
		 * exceptfds - 发生异常的描述符集合
		 * timeout - 超时时间
		 */
		result = select(FD_SETSIZE, &testfds, (fd_set *)NULL, (fd_set *)NULL,
				&timeout);

		switch(result) {
		case 0:
			printf("timeout\n");
			break;
		case -1:
			perror("select");
			exit(1);
		default:
			/*
			 * FD_ISSET - tests to see if a file descriptor is part of the set
			 */
			if(FD_ISSET(0, &testfds)) {
				/*
				 * FIONREAD - 获取接收缓存区中的字节数
				 */
				ioctl(0, FIONREAD, &nread);
				if(nread == 0) {
					printf("keyboard done\n");
					exit(0);
				}
				nread = read(0, buffer, nread);
				buffer[nread] = 0;
				printf("read %d from keyboard: %s", nread, buffer);
			}
			break;
		}
	}
}
