/*
 * 多进程并发服务器 - 客户端程序
 */

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PORT 2088
#define MAXLINE 100

int main(int argc, char *argv[])
{
	int fd, n;
	char sendline[MAXLINE], recvline[MAXLINE];
	struct hostent *he;
	struct sockaddr_in server;

	if(argc != 2) {
		printf("Usage: %s <IP address>\n", argv[0]);
		exit(1);
	}
	if((he = gethostbyname(argv[1])) == NULL) {
		perror("gethostbyname failed");
		exit(1);	
	}
	if((fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Create socket failed");
		exit(1);
	}

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr = *((struct in_addr *)he->h_addr);

	if(connect(fd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
		perror("connnect failed");
		exit(1);	
	} else
		printf("Connect success!\n");
	
	printf("Input your name:");
	if((fgets(sendline, MAXLINE, stdin)) != NULL)
		write(fd, sendline, strlen(sendline));
	
	printf("Input a string:");
	while(fgets(sendline, MAXLINE, stdin) != NULL) {
		write(fd, sendline, strlen(sendline));
		if((n = recv(fd, recvline, MAXLINE, 0)) == 0) {
			perror("server terminated prematurely");
			exit(1);		
		}
		recvline[n] = '\0';
		printf("receive data from server:%s\n", recvline);
		printf("Input a string:");
	}

	close(fd);
	exit(0);
}
