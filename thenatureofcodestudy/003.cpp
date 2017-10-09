#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

int width = 70, height = 40;
COORD pos;
double sx = 80, sy = 25, bx = 1365, by = 767;

class walker
{
public:
	walker();
	~walker();
	void display();
	void step();
	void draw1();
	void step2();
	void draw2();
	int randright();
	void draw3();
	void randmouse();
	void draw4();
	void rand50(int dirt);
	void rand50inside(int dirt);
	int x;
	int y;
	POINT point;
	HANDLE hOut;
	double divx;
	double divy;

private:

};

walker::walker() {
	x = (int)(sx / 2);
	y = (int)(sy / 2);
	this->hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	divx = bx / sx;
	divy = by / sy;
}

walker::~walker()
{
}

void walker::display() {
	pos.X = x;
	pos.Y = y;
	
	SetConsoleCursorPosition(this->hOut, pos);
	putchar('*');
}

void walker::step() {
	int choice = int(rand() % 4);
	if (choice == 0) {
		x++;
	}
	else if (choice == 1) {
		x--;
	}
	else if (choice == 2) {
		y++;
	}
	else {
		y--;
	}
}

void walker::draw1() {
	this->step();
	this->display();
}

void walker::step2() {
	int stepx = int(rand() % 3) - 1;
	int stepy = int(rand() % 3) - 1;
	x += stepx;
	y += stepy;
}

void walker::draw2() {
	this->step2();
	this->display();
}

double doublerand(double range1, double range2) {
	if (range1 >= range2)
		return NULL;
	return rand() / (double)(RAND_MAX)*(range2 - range1) + range1;

}

int walker::randright() {
	int xxx = rand() % 10;

	if (xxx < 4)
		return this->x++;
	if (xxx < 6)
		return this->x--;
	if (xxx < 8)
		return this->y++;
	if (xxx < 10)
		return this->y--;
}

void walker::draw3() {
	this->randright();
	this->display();

}

void walker::randmouse() {
	int tempx, tempy;
	GetCursorPos(&this->point);
	tempx = (int)(this->point.x / divx);
	tempy = (int)(this->point.y / divy);
	if (tempx == pos.X&&tempy == pos.Y)
		this->rand50(0);
	if (tempx < pos.X&&tempy < pos.Y)
		this->rand50(1);
	if (tempx == pos.X&&tempy < pos.Y)
		this->rand50(2);
	if (tempx > pos.X&&tempy < pos.Y)
		this->rand50(3);
	if (tempx > pos.X&&tempy == pos.Y)
		this->rand50(4);
	if (tempx > pos.X&&tempy > pos.Y)
		this->rand50(5);
	if (tempx == pos.X&&tempy > pos.Y)
		this->rand50(6);
	if (tempx < pos.X&&tempy > pos.Y)
		this->rand50(7);
	if (tempx < pos.X&&tempy == pos.Y)
		this->rand50(8);

}

void walker::draw4() {
	this->randmouse();
	this->display();

}

void walker::rand50(int dirt)
{
	int xxx = rand() % 16;

	switch (dirt)
	{
	case 0:
		if (xxx < 8)
		{
			;
			break;
		}
		if (xxx < 9)
		{
			this->x--;
			this->y--;
			break;
		}
		if (xxx < 10)
		{
			this->y--;
			break;
		}
		if (xxx < 11)
		{
			this->x++;
			this->y--;
			break;
		}
		if (xxx < 12)
		{
			this->x++;
			break;
		}
		if (xxx < 13)
		{
			this->x++;
			this->y++;
			break;
		}
		if (xxx < 14)
		{
			this->y++;
			break;
		}
		if (xxx < 15)
		{
			this->x--;
			this->y++;
			break;
		}
		if (xxx < 16)
		{
			this->x--;
			break;
		}
		break;
	case 1:
		if (xxx < 8)
		{
			this->x--;
			this->y--;
			break;
		}
		if (xxx < 9)
		{
			;
			break;
		}
		if (xxx < 10)
		{
			this->y--;
			break;
		}
		if (xxx < 11)
		{
			this->x++;
			this->y--;
			break;
		}
		if (xxx < 12)
		{
			this->x++;
			break;
		}
		if (xxx < 13)
		{
			this->x++;
			this->y++;
			break;
		}
		if (xxx < 14)
		{
			this->y++;
			break;
		}
		if (xxx < 15)
		{
			this->x--;
			this->y++;
			break;
		}
		if (xxx < 16)
		{
			this->x--;
			break;
		}
		break;
	case 2:
		if (xxx < 8)
		{
			this->y--;
			break;
		}
		if (xxx < 9)
		{
			this->x--;
			this->y--;
			break;
		}
		if (xxx < 10)
		{
			;
			break;
		}
		if (xxx < 11)
		{
			this->x++;
			this->y--;
			break;
		}
		if (xxx < 12)
		{
			this->x++;
			break;
		}
		if (xxx < 13)
		{
			this->x++;
			this->y++;
			break;
		}
		if (xxx < 14)
		{
			this->y++;
			break;
		}
		if (xxx < 15)
		{
			this->x--;
			this->y++;
			break;
		}
		if (xxx < 16)
		{
			this->x--;
			break;
		}
		break;
	case 3:
		if (xxx < 8)
		{
			this->x++;
			this->y--;
			break;
		}
		if (xxx < 9)
		{
			this->x--;
			this->y--;
			break;
		}
		if (xxx < 10)
		{
			this->y--;
			break;
		}
		if (xxx < 11)
		{
			;
			break;
		}
		if (xxx < 12)
		{
			this->x++;
			break;
		}
		if (xxx < 13)
		{
			this->x++;
			this->y++;
			break;
		}
		if (xxx < 14)
		{
			this->y++;
			break;
		}
		if (xxx < 15)
		{
			this->x--;
			this->y++;
			break;
		}
		if (xxx < 16)
		{
			this->x--;
			break;
		}
		break;
	case 4:
		if (xxx < 8)
		{
			this->x++;
			break;
		}
		if (xxx < 9)
		{
			this->x--;
			this->y--;
			break;
		}
		if (xxx < 10)
		{
			this->y--;
			break;
		}
		if (xxx < 11)
		{
			this->x++;
			this->y--;
			break;
		}
		if (xxx < 12)
		{
			;
			break;
		}
		if (xxx < 13)
		{
			this->x++;
			this->y++;
			break;
		}
		if (xxx < 14)
		{
			this->y++;
			break;
		}
		if (xxx < 15)
		{
			this->x--;
			this->y++;
			break;
		}
		if (xxx < 16)
		{
			this->x--;
			break;
		}
		break;
	case 5:
		if (xxx < 8)
		{
			this->x++;
			this->y++;
			break;
		}
		if (xxx < 9)
		{
			this->x--;
			this->y--;
			break;
		}
		if (xxx < 10)
		{
			this->y--;
			break;
		}
		if (xxx < 11)
		{
			this->x++;
			this->y--;
			break;
		}
		if (xxx < 12)
		{
			this->x++;
			break;
		}
		if (xxx < 13)
		{
			;
			break;
		}
		if (xxx < 14)
		{
			this->y++;
			break;
		}
		if (xxx < 15)
		{
			this->x--;
			this->y++;
			break;
		}
		if (xxx < 16)
		{
			this->x--;
			break;
		}
		break;
	case 6:
		if (xxx < 8)
		{
			this->y++;
			break;
		}
		if (xxx < 9)
		{
			this->x--;
			this->y--;
			break;
		}
		if (xxx < 10)
		{
			this->y--;
			break;
		}
		if (xxx < 11)
		{
			this->x++;
			this->y--;
			break;
		}
		if (xxx < 12)
		{
			this->x++;
			break;
		}
		if (xxx < 13)
		{
			this->x++;
			this->y++;
			break;
		}
		if (xxx < 14)
		{
			;
			break;
		}
		if (xxx < 15)
		{
			this->x--;
			this->y++;
			break;
		}
		if (xxx < 16)
		{
			this->x--;
			break;
		}
		break;
	case 7:
		if (xxx < 8)
		{
			this->x--;
			this->y++;
			break;
		}
		if (xxx < 9)
		{
			this->x--;
			this->y--;
			break;
		}
		if (xxx < 10)
		{
			this->y--;
			break;
		}
		if (xxx < 11)
		{
			this->x++;
			this->y--;
			break;
		}
		if (xxx < 12)
		{
			this->x++;
			break;
		}
		if (xxx < 13)
		{
			this->x++;
			this->y++;
			break;
		}
		if (xxx < 14)
		{
			this->y++;
			break;
		}
		if (xxx < 15)
		{
			;
			break;
		}
		if (xxx < 16)
		{
			this->x--;
			break;
		}
		break;
	case 8:
		if (xxx < 8)
		{
			this->x--;
			break;
		}
		if (xxx < 9)
		{
			this->x--;
			this->y--;
			break;
		}
		if (xxx < 10)
		{
			this->y--;
			break;
		}
		if (xxx < 11)
		{
			this->x++;
			this->y--;
			break;
		}
		if (xxx < 12)
		{
			this->x++;
			break;
		}
		if (xxx < 13)
		{
			this->x++;
			this->y++;
			break;
		}
		if (xxx < 14)
		{
			this->y++;
			break;
		}
		if (xxx < 15)
		{
			this->x--;
			this->y++;
			break;
		}
		if (xxx < 16)
		{
			;
			break;
		}
		break;
	default:
		break;
	}
}

void walker::rand50inside(int dirt)
{
}

void main() {
	srand(time(NULL));
	walker w;
	for (int i = 0; i < 1000; i++)
	{
		w.draw4();
		Sleep(200);
	}	
	getchar();
}