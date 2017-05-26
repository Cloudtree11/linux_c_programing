/*
 * TCP 客户端程序
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

#define PORT 1234
#define MASDATASIZE 100

int main(int argc, char* argv[])
{
	int sockfd, num;
	char buf[MASDATASIZE];
	struct sockaddr_in server;
	struct hostent* he;

	if(argc != 2){
		printf("Usage: %s <IP Address>\n", argv[0]);
		exit(1);
	}
	if((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket() error");
		exit(1);
	}

	bzero(&server, sizeof(server));

	server.sin_family = PF_INET;
	server.sin_port = htons(PORT);
	inet_aton(argv[1], &(server.sin_addr));
	if((he = gethostbyname(argv[1])) == NULL) {
		perror("gethostname() error");
		exit(1);
	}
	server.sin_addr = *((struct in_addr*)he->h_addr);

	if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		perror("connect() error");
		exit(1);
	}

	if((num = recv(sockfd, buf, MASDATASIZE, 0)) == -1) {
		perror("recv() error");
		exit(1);
	}
	printf("server message len: %d : %s\n", num, buf);
	close(sockfd);
	return 0;
}
