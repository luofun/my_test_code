///testuse36
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>

int sx = 80, sy = 25, bx = 1365, by = 767;



void main(){

	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { 0 };
	POINT point = { 0 };
	double divx = (double)bx / (double)sx;
	double divy = (double)by / (double)sy;
	int midx = bx / 2;
	int midy = by / 2;
	int paintx, painty;
	double div;
	
	
	while (1)
	{
		
		if (_kbhit())
		{
			_getch();
			GetCursorPos(&point);
			paintx = (int)((point.x - midx) / divx);
			painty = (int)((point.y - midy) / divy);
			printf("%d\t%d\n", paintx, painty);
			div = (double)paintx / (double)painty;
			
		}
	}

	getchar();
}
///end