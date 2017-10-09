#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

int sx = 80, sy = 25;

HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

void main(){

	int px = (int)(sx / 2);
	int py = (int)(sy / 2);
	int xspeed = 2;
	int yspeed = 1;
	COORD pos = { 0 };

	while (1)
	{
		if (px >= 78 || px <= 0)
			xspeed *= -1;
		if (py >= 24 || py <= 0)
			yspeed *= -1;
		px += xspeed;
		py += yspeed;
		pos.X = px;
		pos.Y = py;
		SetConsoleCursorPosition(hOut, pos);
		printf("*");
		
		Sleep(100);
	}



	getchar();
}