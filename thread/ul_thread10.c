/*
 * POSIX 信号量（用于线程）
 */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSTACK 10
int stack[MAXSTACK][2];
int size = 0;
sem_t sem;

void readdata1(void)
{
	FILE *fp = fopen("file1", "r");
	while(!feof(fp)) {
		fscanf(fp, "%d %d", &stack[size][0], &stack[size][1]);
		/* sem_post - 释放信号量 */
		sem_post(&sem);
		++size;
	}
	fclose(fp);
}

void readdata2(void)
{
	FILE *fp = fopen("file2", "r");
	while(!feof(fp)) {
		fscanf(fp, "%d %d", &stack[size][0], &stack[size][1]);
		sem_post(&sem);
		++size;
	}
	fclose(fp);
}

void handledata1(void)
{
	while(1) {
		/* sem_wait - 获取信号量 */
		sem_wait(&sem);
		printf("Plus: %d + %d = %d, size = %d\n", stack[size][0], 
				stack[size][1], stack[size][0] + stack[size][1], size);
		--size;
	}
}

void handledata2(void)
{
	while(1) {
		sem_wait(&sem);
		printf("Multiply: %d * %d = %d, size = %d\n", stack[size][0], 
				stack[size][1], stack[size][0] * stack[size][1], size);
		--size;
	}
}

int main(void)
{
	pthread_t t1, t2, t3, t4;
	/* sem_init - 创建信号量 */
	sem_init(&sem, 0, 0);
	pthread_create(&t1, NULL, (void *)handledata1, NULL);
	pthread_create(&t2, NULL, (void *)handledata2, NULL);
	pthread_create(&t3, NULL, (void *)readdata1, NULL);
	pthread_create(&t4, NULL, (void *)readdata2, NULL);
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	sem_destroy(&sem);
}
