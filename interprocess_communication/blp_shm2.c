
/*
 * 共享内存 —— 消费者
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>

#include "blp_shm_com.h"

int main()
{
	int running = 1;
	void *shared_memory = (void *)0;
	struct shared_use_st *shared_stuff;
	char buffer[BUFSIZ];
	int shmid;

	srand((unsigned int)getpid());

	/* shmget 创建共享内存 */
	shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

	if(shmid == -1) {
		fprintf(stderr, "shmget failed\n");
		exit(EXIT_FAILURE);
	}

	/* 将共享内存连接到进程的地址空间中，描述符 -> 地址指针 */
	shared_memory = shmat(shmid, (void *)0, 0);
	if(shared_memory == (void *)-1) {
		fprintf(stderr, "shmat failed\n");
		exit(EXIT_FAILURE);
	}

	printf("Memory attached at %X\n", (int)shared_memory);

	shared_stuff = (struct shared_use_st *)shared_memory;
	shared_stuff -> written_by_you = 0;
	while(running) {
		while(shared_stuff -> written_by_you == 1) {
			sleep(1);
			printf("Waiting for client...\n");
		}
		printf("Enter some text: ");
		fgets(buffer, BUFSIZ, stdin);

		strncpy(shared_stuff -> some_text, buffer, TEXT_SZ);
		shared_stuff -> written_by_you = 1;

		if(strncmp(shared_stuff -> some_text, "end", 3) == 0)
			running = 0;
	}

	/* shmdt 将共享内存从当前进程中分离 */
	if(shmdt(shared_memory) == -1) {
		fprintf(stderr, "shmdt failed\n");
		exit(EXIT_FAILURE);
	}	

	exit(EXIT_SUCCESS);

}

