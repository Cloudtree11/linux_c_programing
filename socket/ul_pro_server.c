/*
 * 多进程并发 TCP 服务器
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

#define MAXSIZE 100
#define PORT 2088
#define BACKLOG 10

void process_cli(int connectfd, struct sockaddr_in client);
void savedata_r(char *recvbuf, int len, char *savebuf);
int counter = 0;

int main(void)
{
	int listenfd, connectfd;
	struct sockaddr_in server, client;
	int client_len;
	pid_t nchild;
	struct ARG *arg;

	if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("Create socket failed");
		exit(1);
	}

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(listenfd, (struct sockaddr *)&server, 
				sizeof(struct sockaddr)) == -1) {
		perror("Bind error");
		exit(1);
	}

	if(listen(listenfd, BACKLOG)) {
		perror("listen error");
		exit(1);
	}

	client_len = sizeof(struct sockaddr);

	while(1) {
		if((connectfd = accept(listenfd, (struct sockaddr *)&client,
						&client_len)) == -1) {
			perror("accept error");
			exit(1);
		}
		if((nchild = fork()) > 0) {
			/* 父进程关闭连接 socket  */
			close(connectfd);
			continue;
		} else if (nchild == 0) {
			/* 子进程关闭监听 socket  */
			close(listenfd);
			process_cli(connectfd, client);
			exit(0);
		} else {
			printf("fork error\n");
			exit(0);
		}
	}
	close(listenfd);
}

void process_cli(int connectfd, struct sockaddr_in client)
{
	int recNumber, i;
	char buff[MAXSIZE], temp[MAXSIZE], cli_name[MAXSIZE], savebuf[MAXSIZE];
	
	printf("Connect from %s, port is %d\n",
		inet_ntop(AF_INET, &client.sin_addr, buff, sizeof(buff)),
			ntohs(client.sin_port));
	if((recNumber = read(connectfd, cli_name, MAXSIZE)) > 0) {
		cli_name[recNumber - 1] = '\0';
		printf("Client's name is:%s\n", cli_name);
	} else {
		close(connectfd);
		printf("client disconnected.\n");
		return;
	}

	while((recNumber = read(connectfd, buff, MAXSIZE)) > 0) {
		savedata_r(buff, recNumber, savebuf);
		buff[recNumber] = '\0';
		printf("Receive client (%s) message: %s\n", cli_name, buff);

		for(i = 0; i < recNumber - 1; i++) {
			temp[i] = buff[recNumber - i - 2];
		}
		temp[recNumber - 1] = '\0';
		write(connectfd, temp, recNumber - 1);
	}
	printf("all of data from client (%s): %s\n", cli_name, savebuf);
	close(connectfd);
}

void savedata_r(char *recvbuf, int len, char *savebuf)
{
	int k;
	for(k = 0; k < len - 1; k++)
		savebuf[counter++] = recvbuf[k];
	savebuf[counter] = 0;
}
