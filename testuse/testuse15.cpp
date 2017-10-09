#include<stdio.h>


void main() {
	printf("%c\n", 3);
	printf("%c\n", 0x8);
	printf("%x\n", 'M');
	int ttt = 0;
	ttt = (int)'M';
	printf("%d\t%x\n", ttt, ttt);
	printf("%d\t%d\t%d\t%d\n", 0b10000, 00011, 0b01110, 0);
	printf("%c\t%c\t%c\t%c\n", 'A' + 0b10000 - 1, 'A' + 00011 - 1, 'A' + 0b01110 - 1, 0);
}