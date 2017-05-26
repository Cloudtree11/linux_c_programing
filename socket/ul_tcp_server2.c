/*
 * TCP 服务器程序
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
#define BACKLOG 1

int main(int argc, char* argv[])
{
	int listenfd, connectfd;
	struct sockaddr_in server;
	struct sockaddr_in client;
	socklen_t addrlen;
	int opt = SO_REUSEADDR;
	char buf[10];

	if((listenfd = socket(PF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket() error");
		exit(1);
	}

	/* SO_REUSEADDR - 允许重用本地地址 */
	setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	bzero(&server, sizeof(server));

	server.sin_family = PF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd, (struct sockaddr *)&server, sizeof(server)) == -1) {
		perror("bind() error");
		exit(1);
	}

	if(listen(listenfd, BACKLOG) == -1) {
		perror("listen() error");
		exit(1);
	}

	addrlen = sizeof(client);
	if((connectfd = accept(listenfd, (struct sockaddr *)&client, &addrlen)) == -1) {
		perror("accept() error");
		exit(1);
	}

	printf("Client's IP is %s, prot is %d \n", 
			inet_ntoa(client.sin_addr), htons(client.sin_port));

	memset(buf, 8, sizeof(buf));
	strcpy(buf, "Welcome");
	send(connectfd, buf, 10, 0);
	close(connectfd);
	close(listenfd);
	return 0;
}
