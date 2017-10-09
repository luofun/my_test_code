#include <stdio.h>
int main()
{
	unsigned int a = 0x11223344;
	char b;
	b = *(char *)&a;
	if (b == 0x11)
	{
		printf("big endian!\n");
	}
	else if (b == 0x44)
	{
		printf("little endian !\n");
	}
	union w
	{
		int a;  //4 bytes
		char b; //1 byte
	} c;
	c.a = 1;
	if (c.b == 1)
		printf("It is Little_endian!\n");
	else
		printf("It is Big_endian!\n");
	
	getchar();

	return 0;
}