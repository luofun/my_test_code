#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>

void main() {

	srand(time(NULL));

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	int xxx[80] = { 0 };
	int temp = 0;
	COORD pos = { 0 };


	for (int i = 0; i < 80; i++)
	{
		printf("!");
	}

	for (int i = 0; i < 4000; i++)
	{
		temp = rand() % 80;
		xxx[temp]++;
		pos.X = temp;
		pos.Y = xxx[temp] + 1;
		SetConsoleCursorPosition(hOut, pos);
		printf("*");
		//Sleep(30);
	}



	getchar();
}