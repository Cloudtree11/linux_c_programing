
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_function(void *arg);

char message[] = "Hello World";
int thread_finished = 0;

/* 设置脱离状态属性（执行完直接中止，不返回消息给主线程） */

int main()
{
	int res;
	pthread_t a_thread;

	pthread_attr_t thread_attr;

	/* 初始化线程属性  */
	res = pthread_attr_init(&thread_attr);
	if(res != 0) {
		perror("Attribute creation failed");
		exit(EXIT_FAILURE);
	}
	/* detachstate 允许无须对线程重新合并，
	 * PTHREAD_CREATE_DETACHED 无法调用 pthread_join 来获得另一个线程退出状态 */
	res = pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED);
	if(res != 0) {
		perror("Setting detached attribute failed");
		exit(EXIT_FAILURE);
	}
	res = pthread_create(&a_thread, &thread_attr,
			thread_function, (void *)message);
	if(res != 0) {
		perror("Thread creation failed");
		exit(EXIT_FAILURE);
	}
	/* 清理和回收属性对象 */
	(void)pthread_attr_destroy(&thread_attr);
	while(!thread_finished) {
		printf("Waiting for thread to say it's finished...\n");
		sleep(1);
	}
	printf("Other thread finished, bye!\n");
	exit(EXIT_SUCCESS);

}

void *thread_function(void *arg)
{
	printf("thread_function is running. Argument was %s\n", (char *)arg);
	sleep(4);
	printf("Second thread setting finished flag, and exiting now\n");
	thread_finished = 1;
	pthread_exit(NULL);
}
