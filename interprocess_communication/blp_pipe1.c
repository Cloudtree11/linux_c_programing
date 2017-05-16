
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* pipe 系统调用  */

int main()
{
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "1234567890";
	char buffer[BUFSIZ + 1];

	memset(buffer, '\0', sizeof(buffer));

	if(pipe(file_pipes) == 0) {
		/* 写到 file_pipes[1] 的数据可以从 file_pipes[0] 读回来  */
		data_processed = write(file_pipes[1], some_data, strlen(some_data));
		printf("Wrote %d bytes\n", data_processed);
		data_processed = read(file_pipes[0], buffer, BUFSIZ);
		printf("Read %d bytes: %s\n", data_processed, buffer);
		exit(EXIT_SUCCESS);
	}
	exit(EXIT_FAILURE);
}




