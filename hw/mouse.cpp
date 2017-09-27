#include<stdio.h>
#include<Windows.h>


void main(){

	Sleep(1000);
	printf("test begin!\n");
	int suibiao = 1;
	POINT testbiao = { 0, 0 };

	while (getchar() != 'q')
	{
		if (suibiao == 1)
		{
			GetCursorPos(&testbiao);
			printf("\nsuibiao:  %d  %d\n", testbiao.x, testbiao.y);
			Sleep(1000);
		}

	}

	printf("thanks!\n");
}