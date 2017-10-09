#include<stdio.h>

//int aaa[10000000] = { 0 };

int main()
{
	int a = 1, b = 2, c = 0;

	// 蛋疼的 add 操作  
	__asm {
		push eax    // 保护 eax  

		mov eax, a  // eax = a;  
		add eax, b  // eax = eax + b;
		add eax, 0x2
		add eax, 10
		mov c, eax  // c = eax;  

		pop eax     // 恢复 eax  
	}

	int asm1, asm2, asm3, asm4;
	asm1 = 0;
	asm2 = 0;
	asm3 = 0;
	asm4 = 0;

	__asm {
		mov asm1, ecx
		mov asm2, esp
		mov asm3, ebp
	}

	__asm {
		push eax
		push ebx
		mov eax, 4
		mov ebx, 3
		imul ebx
		mov asm4, eax
		pop eax
		pop ebx
	}

	__asm {
		mov eax, 100
	
	}

	int asm5 = 0;

	__asm {
		mov asm5, eax
	}

	__asm {
		add eax, 1
		mov asm5, eax
		mov eax, 0;
	}

	__asm {
		add asm5, 10
	}

	__asm {
		mov asm5, ebx
	}

	/*__asm {
		mov ebp, 0
		mov esp, 0
	}*/

	/*__asm {
		int 3
	}*/

	__int16 test;

	__asm {
		mov test, cs
	}

	

	printf("asm test\n\n");

	printf("现在c是:%d\n", c);
	
	printf("\n\nother:\n1:\t0x%x\n2:\t0x%x\n3:\t0x%x\n", asm1, asm2, asm3);

	printf("diff:\t%d\n", asm3 - asm2);

	/*__asm {
		int 3
	}//use4debug
	*/

	printf("4:\t%d\n", asm4);

	printf("5:\t%d\n", asm5);

	printf("test:\t%d\n", test);

	return 0;
}