
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void ouch(int sig)
{
	printf("OUCH! - I got signal %d\n", sig);
}

int main()
{
	struct sigaction act;

	act.sa_handler = ouch;
	sigemptyset(&act.sa_mask); /* sigemptyset 设置空信号屏蔽字 */
	act.sa_flags = 0;

	sigaction(SIGINT, &act, 0); /* 使用更健壮的信号接口取代 signal */

	while(1) {
		printf("Hello World!\n");
		sleep(1);
	}
}
