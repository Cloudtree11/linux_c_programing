
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * exec�������԰ѵ�ǰ�����滻Ϊһ���½��̣��������ִ�д�һ�������л�Ϊ��һ������
 * ���µĳ���ִ�к�ԭ���ĳ���Ͳ��������ˡ�
 */


int main()
{
	printf("Running ps with execlp\n");
	execlp("ps", "ps", "ax", 0);
	printf("Done.\n");
	exit(0);
}

