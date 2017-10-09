#include<stdio.h>

struct MyStruct
{
	unsigned int x : 3;
	char y;
	int z : 5;
	int a;
};

void main() {
	
	printf("%d\n", sizeof(MyStruct));

	MyStruct test;

	test.x = 0b111;

	printf("%d\n", test.x);

}