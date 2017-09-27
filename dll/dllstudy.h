#define DLL_API __declspec(dllexport)  
#include<iostream>  
using namespace std;

DLL_API int add(int a, int b);
class DLL_API Point
{
private:
	float x, y;
public:
	Point();
	void SetPoint(float a, float b);
	void DisPlay();
};