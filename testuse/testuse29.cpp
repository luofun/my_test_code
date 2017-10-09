#include <stdio.h>

#define SIZE (1 << 4)
int main()
{
	int x, y, i;
	for (y = SIZE - 1; y >= 0; y--, putchar('\n')) {
		for (i = 0; i < y; i++) putchar(' ');
		for (x = 0; x + y < SIZE; x++)
			printf((x & y) ? "  " : "* ");
	}
	//printf("\n%d\n", SIZE);
	getchar();
	
	return 0;
}