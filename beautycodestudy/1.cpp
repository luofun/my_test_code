#include<stdio.h>
#include<Windows.h>

void test1(){
	for (;;)
	{
		for (int i = 0; i < 9600000; i++)
			;
		Sleep(10);
	}
}

void test2(){
	int busytime = 10;
	int idletime = busytime;
	INT64 starttime = 0;
	while (true)
	{
		starttime = GetTickCount();
		while (GetTickCount() - starttime <= busytime)
			;
		Sleep(idletime);
	}
	

}


void main(){
	//test1();
	test2();

}