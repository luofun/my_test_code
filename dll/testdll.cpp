//#pragma comment(dll,"test.dll")
#include<stdio.h>
#include <Windows.h>
#include <tchar.h>
void main()
{
	HMODULE hModule = NULL;
	typedef int(*Func)(int a, int b);
	hModule = LoadLibrary(_T("test.dll"));
	Func fAdd = (Func)GetProcAddress(hModule, "add");
	printf("%d\n", fAdd(5, 2));
	FreeLibrary(hModule);//¶¯Ì¬¿â
	//printf("%d\n", 1 << 4);
}

#if 0

#include<MakeDll.h>  
#define DLL_API __declspec(dllimport)  
#pragma comment(lib,"MakeDll.lib")  
int main()  
{  
    Point p1, p2;  
    p2.SetPoint(5.6f, 7.8f);  
    p1.Display();  
    p2.Display();  
    cout << "5+6 = " << add(5, 6) << endl;  
    return 0;  
}  

#endif