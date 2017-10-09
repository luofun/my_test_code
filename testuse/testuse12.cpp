#include<stdio.h>
#include <windows.h>

//声明引用外部函数
EXTERN_C ULONG64 myAdd(ULONG64 u1, ULONG64 u2);

int main(int argc, char* argv[])
{
	ULONG64 result = myAdd(0x111111111, 0x333333333);
	printf("result = 0x%I64X\n", result);
	return 0;
}