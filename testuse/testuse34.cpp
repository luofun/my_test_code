///testuse34
#include <random>
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

void main() {
	double x;
	COORD pos;
	pos.X = 40;
	pos.Y = 12;
	int sx = 80, sy = 25;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::random_device xrd, yrd;
	std::mt19937 xgen(xrd()), ygen(yrd());
	std::normal_distribution<double> xd(40, 3);
	std::normal_distribution<double> yd(12, 3);
	for (int i = 0; i < 1000; ++i)
	{		
		pos.X = (int)(xd(xgen) + 0.5);
		pos.Y = (int)(yd(ygen) + 0.5);
		SetConsoleCursorPosition(hOut, pos);
		putchar('*');
	}
	
	getchar();
}
///end

