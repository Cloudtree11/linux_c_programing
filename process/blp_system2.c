
#include <stdlib.h>
#include <stdio.h>

/*
 * ʹ��system����Զ�������������̵������ֶΣ���Ϊ��������һ��shell��������Ҫ�ĳ���
 * Ч�ʲ���
 */

int main()
{
	printf("Running ps with system\n");
	system("ps ax &");
	printf("Done.\n");
	exit(0);
}
