#include"dllstudy.h"  
DLL_API int add(int a, int b)
{
	return a + b;
}
Point::Point()
{
	x = 0.0f;
	y = 0.0f;
}
void Point::SetPoint(float x, float y)
{
	this->x = x;
	this->y = y;
}

void Point::DisPlay(){
	cout << "x= " << x << endl;
	cout << "y= " << y << endl;
}