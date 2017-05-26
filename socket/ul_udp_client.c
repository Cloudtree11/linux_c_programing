/*
 * UDP 客户端程序
 */
#include <stdio.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#define PORT 1234
#define MAXDATASIZE 100

int main(int argc, char *argv[])
{
	int fd, numbytes, len;
	char buf[MAXDATASIZE];
	struct hostent *he;
	struct sockaddr_in server, reply;
	
	if(argc != 3) {
		printf("Usage: %s <IP address> <message>\n", argv[0]);
		exit(1);
	}

	if((he = gethostbyname(argv[1])) == NULL) {
		printf("gethostbyname() error\n");
		exit(1);	
	}

	if((fd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
		printf("socket() error\n");
		exit(1);
	}

	bzero(&server, sizeof(server));
	server.sin_family = PF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr = *((struct in_addr *)he->h_addr);

	sendto(fd, argv[2], strlen(argv[2]), 0, 
			(struct sockaddr *)&server, sizeof(struct sockaddr));

	while(1) {
		if((numbytes = recvfrom(fd, buf, MAXDATASIZE, 0,
						(struct sockaddr *)&reply, &len)) == -1) {
			printf("recvfrom() error\n");
			exit(1);
		}
		buf[numbytes] = '\0';
		printf("Server Message: %s\n", buf);
		break;
	}
	close(fd);
}
