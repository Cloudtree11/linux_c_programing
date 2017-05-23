/*
 * 消息队列- 发送消息
 */
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string.h>
#include <sys/errno.h>

extern int errno;
struct mymsgbuf {
	long mtype;
	char ctext[100];
};

int main()
{
	struct mymsgbuf buf;
	int msid;

	if((msid = msgget(0x1000, 0666 | IPC_CREAT)) < 0) {
		fprintf(stderr, "open msg %X failed.\n", 0x1000);
		exit(1);
	}

	while(strncmp(buf.ctext, "exit", 4)) {
		memset(&buf, 0, sizeof(buf));
		fprintf(stderr, "Please input: ");
		fgets(buf.ctext, sizeof(buf.ctext), stdin);
		buf.mtype = 100;
		while((msgsnd(msid, &buf, strlen(buf.ctext), 0)) < 0) {
			if (errno == EINTR)
				continue;
			exit(1);
		}
	}
}
