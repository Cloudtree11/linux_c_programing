/*
 * 消息队列 - 接收程序
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
	int ret;

	if((msid = msgget(0x1000, 0666 | IPC_CREAT)) < 0) {
		fprintf(stderr, "open msg %X failed.\n", 0x1000);
		exit(1);
	}

	while(strncmp(buf.ctext, "exit", 4)) {
		memset(&buf, 0, sizeof(buf));
		while((ret = msgrcv(msid, &buf, sizeof(buf.ctext), 0, 0)) < 0) {
			if(errno == EINTR) continue;
			exit(1);
		}
		fprintf(stderr, "Msg: Tyoe=%d, Len=%d, Text:%s", buf.mtype, ret, buf.ctext);
	}

	if(msgctl(msid, IPC_RMID, NULL)) {
		fprintf(stderr, "Delete msg failed.\n");
		exit(1);
	}
}
