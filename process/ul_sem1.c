/*
 * 创建、读取和删除信号量等操作 
 */
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <stdio.h>

#define VerifyErr(a, b) \
	if (a) fprintf(stderr, "%s failed.\n", (b)); \
	else (stderr, "%s success.\n", (b));

int main(int argc, char *argv[])
{
	int semid, index, i;
	unsigned short array[100];
	struct semid_ds ds;
	if(argc != 4)
		return 0;

	semid = atoi(argv[1]);
	index = atoi(argv[2]);
	if(argv[3][0] == 'c') {
		VerifyErr(semget(semid, index, 0666 | IPC_CREAT | IPC_EXCL) < 0, "Create sem");
	} else if(argv[3][0] == 'd'){
		VerifyErr(semctl(semid, 0, IPC_RMID, NULL) < 0, "Delete sem");
	} else if(argv[3][0] == 'v'){
		fprintf(stderr, "T ID INDEX SEMVAL SEMIPID SEMNCNT SEMZCNT\n");
		fprintf(stderr, "s %6d %6d %10d %10d %10d %10d\n", semid, index,
				semctl(semid, index, GETVAL), semctl(semid, index, GETPID),
				semctl(semid, index, GETNCNT), semctl(semid, index, GETZCNT));
	} else if(argv[3][0] == 'a'){
		ds.sem_nsems = 0;
		VerifyErr(semctl(semid, 0, IPC_STAT, &ds) != 0, "Get Sem Stat");
		VerifyErr(semctl(semid, 0, GETALL, array) != 0, "Get Sem All");
		for(i = 0; i < ds.sem_nsems; i++)
			fprintf(stderr, "sem no [%d]: [%d]\n", i, array[i]);
	} else {
		VerifyErr(semctl(semid, index, SETVAL, atoi(argv[3])) != 0, "Set Sem Val");
	}

	return 0;

}
