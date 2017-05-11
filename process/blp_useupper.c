
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *filename;

	if(argc != 2) {
		fprintf(stderr, "usage: useupper file\n");
		exit(1);
	}

	filename = argv[1];

	if(!freopen(filename, "r", stdin)) { /* freopen 先关闭标准输入，再将文件流 stdin 与
											程序参数给定的文件名关联起来*/
		fprintf(stderr, "could not redirect stdin from file %s \n", filename);
		exit(2);
	}

	execl("./upper", "upper", 0); /* 已打开的文件描述符会在 execl 调用后保留 */

	perror("could not exec ./upper");
	exit(3);
}



