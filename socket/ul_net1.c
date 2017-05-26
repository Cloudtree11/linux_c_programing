
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>

int main(int argc, int **argv)
{
	struct hostent *host = NULL;
	struct servent *serv = NULL;
	char *host_ip = NULL;
	if(argc != 3) return 1;
	if(strcmp(argv[1], "DNS") == NULL) {
		if((host = gethostbyname(argv[2])) == NULL) {
			printf("gethostbyname error!\n");
			return 2;
		}
		/* 
		 * char *inet_ntoa(struct in_addr in)
		 * Converts the Internet host address in, given in network
		 *        byte order, to a string in IPv4 dotted-decimal notation.
		 */
		host_ip = inet_ntoa(*((struct in_addr*)host->h_addr));
		printf("Host name: %s\n", host -> h_name);
		//printf("Host IP: %s\n", host_ip);
	} else if (strcmp(argv[1], "SERV") == NULL) {
		if((host = getservbyname(argv[2], "tcp")) == NULL) {
			printf("getservbyname error!\n");
			return 2;
		}
		printf("Serv name: %s\n", serv -> s_name);
		printf("Serv Port: %d\n", ntohs(serv -> s_port));
	}
}

