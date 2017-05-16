
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 管道和 dup 函数  */

int main()
{
	int data_processed;
	int file_pipes[2];
	const char some_data[] = "1234567890";
	pid_t fork_result;

	if(pipe(file_pipes) == 0) {
		fork_result = fork();
		if(fork_result == -1) {
			fprintf(stderr, "Fork failure");
			exit(EXIT_FAILURE);
		}
		if(fork_result == (pid_t)0) {
			/* 关闭标准输入  */
			close(0);
			/* 0 会和 file_pipes[0] 指向同一个文件（读管道） */
			dup(file_pipes[0]);
			/* file_pipes[0] 和 file_pipes[1] 描述符都不需要了，关闭 */
			close(file_pipes[0]);
			close(file_pipes[1]);
			execlp("od", "od", "-c", (char *)0);
			exit(EXIT_FAILURE);
		} else {
			/* 不需要读管道，关闭 file_pipes[0]  */
			close(file_pipes[0]);
			data_processed = write(file_pipes[1], some_data, strlen(some_data));
			/* 写管道完毕，关闭 file_pipes[1] */
			close(file_pipes[1]);
			printf("%d - Wrote %d bytes\n", getpid(), data_processed);
			exit(EXIT_SUCCESS);
		}
	}
	exit(EXIT_FAILURE);
}




