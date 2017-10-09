#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>

//#define width 10
//#define height 10

int width = 70, height = 40;
COORD pos;

void size(int& x, int& y) {
	width = x;
	height = y;
}

class walker
{
public:
	walker();
	~walker();
	void display();
	void step();
	void draw();
	void step2();
	void draw2();
	int x;
	int y;

private:

};

walker::walker() {
	x = width / 2;
	y = height / 2;
}

walker::~walker()
{
}

void walker::display() {
	//stroke(0);
	//point(x, y);
	pos.X = x;
	pos.Y = y;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOut, pos);
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

void walker::draw() {
	this->step();
	this->display();
}

void walker::step2() {
	//Yields - 1, 0, or 1
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

void main() {
	srand(time(NULL));
	walker w;
	for (int i = 0; i < 100; i++)
		w.draw2();
	getchar();
}