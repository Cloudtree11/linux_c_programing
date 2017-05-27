/*
 * IO 多路复用并发的服务器程序
 */
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <malloc.h>
#include <sys/select.h>
#include <fcntl.h>

#define MAXSIZE 100
#define PORT 2088
#define BACKLOG 10

typedef struct CLIENT {
	int fd;
	char *name;
	struct sockaddr_in client_addr;
	char *data;
} CLIENT;

void process_cli(CLIENT *client, char *recvbuf, int len);

int main(void)
{
	int i, maxi, maxfd, sockfd;
	int nready;
	ssize_t n;
	fd_set rset, allset;
	int listenfd, connectfd;
	struct sockaddr_in server, addr;
	CLIENT client[FD_SETSIZE];
	char recvbuf[MAXSIZE], buff[MAXSIZE];
	int sin_size;
	int opt;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Create socket failed");
		exit(1);
	}

	opt = SO_REUSEADDR;
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd, (struct sockaddr *)&server, 
				sizeof(struct sockaddr)) == -1) {
		perror("Bind error");
		exit(1);
	}

	if(listen(listenfd, BACKLOG) == -1) {
		perror("listen error");
		exit(1);
	}

	maxfd = listenfd;
	maxi = -1;

	for(i = 0; i < FD_SETSIZE; i++)
		client[i].fd = -1;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	while(1) {
		rset = allset;
		nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
		if(FD_ISSET(listenfd, &rset)) {
			sin_size = sizeof(addr);
			if((connectfd = accept(listenfd, (struct sockaddr *)&addr,
							&sin_size)) == -1) {
				perror("accept error");
				continue;
			}
			for(i = 0; i < FD_SETSIZE; i++) {
				if(client[i].fd < 0) {
					client[i].fd = connectfd;
					client[i].name = (char *)malloc(MAXSIZE);
					client[i].client_addr = addr;
					client[i].data = (char *)malloc(MAXSIZE);
					client[i].name[0] = '\0';
					client[i].data[0] = '\0';
					printf("You got a connect from: %s port: %d\n",
							inet_ntoa(client[i],.client_addr.sin_addr),
							ntohs(client[i].client_addr.sin_port));
					break;
				}
				if(i == FD_SETSIZE)
					printf("too many clients.\n");
				FD_SET(connectfd, &allset);
				if(connectfd > maxfd)
					maxfd = connectfd;
				if(i > max) maxi = i;
				if(--nready <= 0) continue;
			}
			for(i = 0; i < maxi; i++) {
				if((sockfd = client[i].fd) < 0)
					continue;
				if(FD_ISSET(sockfd, &rset)) {
					if((n = recv(sockfd, recvbuf, MAXSIZE, 0)) == 0) {
						close(sockfd);
						printf("Client (%s) closed connection. User's data: %s\n",
								client[i].name, client[i].data);
						FD_CLR(sockfd, &allset);
						client[i].fd = -1;
						free(client[i].name);
						free(client[i].data);
					} else {
						process_cli(&client[i], recvbuf, n);
						if(--nready <= 0) break;
					}
				}
			}
		}
	}

	close(listenfd);
}

void process_cli(CLIENT *client, char *recvbuf, int len)
{
	char sendbuf[MAXSIZE];
	recvbuf[len - 1]=0;
	if(strlen(client->name) == 0) {
		memcpy(client->name, recvbuf, len);
		printf("client's name is %s\n", client->name);
		return;
	}
	printf("receive client (%s) message: %s \n", client->name, recvbuf);
	strcat(client->data, recvbuf);
	send(clinet->fd, recvbuf, strlen(recvbuf), 0);
}

