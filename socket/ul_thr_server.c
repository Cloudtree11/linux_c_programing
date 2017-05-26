/*
 * 多线程并发 TCP 服务器
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
#include <pthread.h>

#define MAXSIZE 100
#define PORT 2088
#define BACKLOG 10

static void* doit(void *arg);
void process_cli(int connectfd, struct sockaddr_in client);
void savedata_r(char *recvbuf, int len, char *savebuf);
struct ARG {
	int connfd;
	struct sockaddr_in client;
};
static pthread_key_t key = NULL;
static pthread_once_t once = PTHREAD_ONCE_INIT;
static void destructor(void *ptr)
{
	free(ptr);
}
static void getkey_once(void)
{
	pthread_key_create(&key, destructor);
}
typedef struct INDEX {
	int index;
} TSD_INDEX;

int main(void)
{
	int listenfd, connectfd;
	struct sockaddr_in server, client;
	int client_len;
	pthread_t tid;
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

	if(listen(listenfd, BACKLOG) == -1) {
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
		arg = (struct ARG *)malloc(sizeof(struct ARG));
		if(arg == NULL) {
			printf("malloc failed!\n");
			exit(1);
		}
		arg->connfd = connectfd;
		memcpy((void *)&arg->client, (void *)&client,
				sizeof(struct sockaddr_in));
		
		if(pthread_create(&tid, NULL, &doit, (void*)arg) > 0) {
			perror("pthread_create error");
			free(arg);
			continue;
		}
	}
		
	close(listenfd);
}

static void *doit(void *arg)
{
	struct ARG *info;
	info = (struct ARG*)arg;
	process_cli(info->connfd, info->client);
	free(arg);
	pthread_exit(NULL);
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
	TSD_INDEX *data;
	pthread_once(&once, getkey_once);

	if((data=(TSD_INDEX *)pthread_getspecific(key)) == NULL) {
		data = (TSD_INDEX *)calloc(1, sizeof(TSD_INDEX));
		pthread_setspecific(key, data);
		data->index = 0;
	}

	for(k = 0; k < len-1; k++)
		savebuf[data->index++] = recvbuf[k];
	savebuf[data->index] = 0;
}
