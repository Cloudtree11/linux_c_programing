
/* 使用信号量 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <sys/sem.h>

#include "blp_semun.h"

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);
static int semaphore_v(void);

static int sem_id;

int main(int argc, char *argv[])
{
	int i;
	int pause_time;
	char op_char = 'O';

	srand((unsigned int)getpid());

	/* semget 通过一个随意选取的 key 来取得一个信号量标示符
	 * IPC_CREAT 如果信号量不存在，就创建它 */
	sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

	if(argc > 1) {
		if(!set_semvalue()) {
			fprintf(stderr, "Failed to initialize semaphore\n");
			exit(EXIT_FAILURE);
		}
		op_char = 'X';
		sleep(2);
	}

	for(i = 0; i < 10; i++) {
		if(!semaphore_p()) exit(EXIT_FAILURE);
		printf("%c", op_char); fflush(stdout);
		pause_time = rand() % 3;
		sleep(pause_time);
		printf("%c", op_char); fflush(stdout);

		if(!semaphore_v()) exit(EXIT_FAILURE);

		pause_time = rand() % 2;
		sleep(pause_time);
	}

	printf("\n%d - finished\n", getpid());

	if(argc > 1) {
		sleep(10);
		del_semvalue();
	}

	exit(EXIT_SUCCESS);

}

static int set_semvalue(void)
{
	union semun sem_union;

	sem_union.val = 1;
	/* semctl 直接控制信号量信息
	 * SETVAL 将信号量初始化为 semun 中 val 指定的值 */
	if (semctl(sem_id, 0, SETVAL, sem_union) == -1) return 0;
	return 1;
}

static void del_semvalue(void)
{
	union semun sem_union;

	/* 删除信号量标识符 */
	if(semctl(sem_id, 0, IPC_RMID, sem_union) == 1)
		fprintf(stderr, "Failed to delete semaphore\n");
}

/* semaphore_p 对信号量做减 1 操作（等待） */
static int semaphore_p(void)
{
	struct sembuf sem_b;

	/* sem_num 信号量编号，一般为 0 */
	sem_b.sem_num = 0;
	/* sem_op 信号量在一次操作需要改变的数值，通常用 -1 和 1 */
	sem_b.sem_op = -1; /* P() */
	/* SEM_UNDO 使得操作系统跟踪当前进程对这个信号量的修改情况 */
	sem_b.sem_flg = SEM_UNDO;
	/* semop 改变信号量的值 */
	if(semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semaphore_p failed\n");
		return 0;
	}
	return 1;
}

/* semaphore_v “释放”操作，使信号量可用  */
static int semaphore_v(void)
{
	struct sembuf sem_b;

	sem_b.sem_num = 0;
	sem_b.sem_op = 1; /* V() */
	sem_b.sem_flg = SEM_UNDO;
	if(semop(sem_id, &sem_b, 1) == -1) {
		fprintf(stderr, "semaphore_v failed\n");
		return 0;
	}
	return 1;
}




