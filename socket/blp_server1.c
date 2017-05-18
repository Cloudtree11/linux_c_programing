/*
 * 一个简单的本地 socket 服务器
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;

	unlink("server_socket");
	/* socket 创建 socket 并返回描述符
	 * AF_UNIX 指定 socket 域（协议族）为 UNIX 域协议（文件系统 socket）
	 * SOCK_STREAM 指定 socket 类型为 stream （TCP 连接）*/
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);

	/* sun_family 指定地址类型（socket 域）
	 * sun_path 指定 socket 地址 */
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	/* bind 将地址分配给文件描述符关联的未命名 socket 
	 * AF_UNIX socket 关联到文件系统路径名 */
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	/* listen 创建队列保存未处理的请求 */
	listen(server_sockfd, 5);
	while(1) {
		char ch;

		printf("server waiting\n");

		client_len = sizeof(client_address);
		/* accept 等待客户建立对该 socket 的连接 */
		client_sockfd = accept(server_sockfd,
				(struct sockaddr *)&client_address, &client_len);

		read(client_sockfd, &ch, 1);
		ch++;
		write(client_sockfd, &ch, 1);
		close(client_sockfd);
	}
}


