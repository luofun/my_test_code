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