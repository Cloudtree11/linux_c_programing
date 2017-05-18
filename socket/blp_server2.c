/*
 * 网络 socket 服务器
 */

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_in server_address;
	struct sockaddr_in client_address;

	/* 
	 * socket 创建 socket 并返回描述符
	 * AF_UNIX 指定 socket 域（协议族）为 ARPA 因特网协议（UNIX 网络 socket）
	 * SOCK_STREAM 指定 socket 类型为 stream （TCP 连接）
	 */
	server_sockfd = socket(AF_INET, SOCK_STREAM, 0);

	/* 
	 * sin_family 指定地址类型（socket 域）
	 * sin_addr.s_addr 指定允许连接 socket 地址（IP 地址） 
	 * sin_port 指定端口号 
	 */
	server_address.sin_family = AF_INET;
	//server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	/* 
	 * htonl host to network, long（长整数从主机字节序到网络字节序的转换）
	 * htons host to network, short（短整数从主机字节序到网络字节序的转换）
	 * INADDR_ANY 允许来自计算机任何网络接口的连接
	 */
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);
	server_address.sin_port = htons(9734);
	server_len = sizeof(server_address);
	/* 
	 * bind 将地址分配给文件描述符关联的未命名 socket 
	 * AF_UNIX socket 关联到文件系统路径名 
	 */
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


