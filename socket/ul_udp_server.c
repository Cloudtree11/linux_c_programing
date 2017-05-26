/*
 * UDP 服务器程序
 */
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 1234
#define MAXDATASIZE 100

int main()
{
	int sockfd;
	struct sockaddr_in server;
	struct sockaddr_in client;
	int sin_size;
	int num;
	char msg[MAXDATASIZE];

	if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
		perror("Creating socket failed");
		exit(1);
	}

	bzero(&server, sizeof(server));
	server.sin_family = PF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1) {
		perror("Bind error");
		exit(1);
	}

	sin_size = sizeof(struct sockaddr_in);
	while(1) {
		num = recvfrom(sockfd, msg, MAXDATASIZE, 0, 
				(struct sockaddr *)&client, &sin_size);
		if(num < 0) {
			perror("recvfrom error");
			exit(1);
		}
		msg[num] = '\0';
		printf("You got a message (%s) from %s\n", 
				msg, inet_ntoa(client.sin_addr));
		sendto(sockfd, "Welcome to my server.\n", 22, 0, 
				(struct sockaddr *)&client, sin_size);
		if(!strcmp(msg, "quit")) break;
	}
	close(sockfd);

}
