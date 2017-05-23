/*
 * 共享内存 shm - 写数据
 */
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main()
{
	int shmid;
	char *pmat = NULL;
	char buf[1024];
	int no;

	if((shmid = shmget(0x5678, 10 * 1024, 0666 | IPC_CREAT)) == -1) {
		fprintf(stderr, "shmget failed.\n");
		exit(1);
	}

	if((pmat = (char *)shmat(shmid, 0, 0)) == 0) {
		fprintf(stderr, "shmat failed.\n");
		exit(1);
	}

	printf("Please Input Memory No.(0~9): ");
	scanf("%d", &no);
	if(no < 0 || no > 9) {
		fprintf(stderr, "Select Memory block failed.\n");
		exit(1);
	}

	printf("Please Input Data:");
	memset(buf, 0, sizeof(buf));
	scanf("%s", buf);
	memcpy(pmat + no * 1024, buf, 1024);
	shmdt(pmat);
}
