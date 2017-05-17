/*
 * 消息队列 - 发送者
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st {
	long int my_msg_type;
	char some_text[MAX_TEXT];
};

int main()
{
	int running = 1;
	int msgid;
	struct my_msg_st some_data;
	char buffer[BUFSIZ];

	/* msgget 创建和访问一个消息队列 */
	msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

	if(msgid == -1) {
		fprintf(stderr, "msgget failed with error: %d", errno);
		exit(EXIT_FAILURE);
	}

	while(running) {
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);
		some_data.my_msg_type = 1;
		strcpy(some_data.some_text, buffer);

		/* msgsnd 把消息添加到消息队列 */
		if(msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {
			fprintf(stderr, "msgsnd failed\n");
			exit(EXIT_FAILURE);
		}

		if(strncmp(buffer, "end", 3) == 0)
			running = 0;
	}

	exit(EXIT_SUCCESS);

}