/*
 * 无名管道 popen
 * ps -ef | grep grep Server
 */
#include <stdio.h>

int main()
{
	FILE *out, *in;
	char buf[255];

	if((out = popen("grep Server", "w")) == NULL) {
		fprintf(stderr, "error!\n");
		exit(1);
	}
	if((in = popen("ps -ef", "r")) == NULL) {
		fprintf(stderr, "error!\n");
		exit(1);
	}

	while(fgets(buf, sizeof(buf), in))
		fputs(buf, out);

	pclose(out);
	pclose(in);
	exit(0);

}
