#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#ifdef _WIN32
//define something for Windows (32-bit and 64-bit, this part is common)
#include <windows.h>
	#ifdef _WIN64
	//define something for Windows (64-bit only)
	#else
	//define something for Windows (32-bit only)
	#endif
#elif __linux__
// linux
#include <unistd.h>
#elif __unix__
// Unix
#include <unistd.h>
#endif

void clear_the_srceen(){
	#ifdef _WIN32
	system("cls");
	#elif __linux__
	system("clear");
	#endif
}

int main(int agrc, char* agrv[]){
	
	printf("loading...");
	for (int i = 0; i < 10; i++) {
		printf(".");
		Sleep(1000);
	}
	clear_the_srceen();
	printf("begin tool2018-10-10...\n");

	if (agrc < 3){
		printf("too less arg!\n");
		printf("useage: tools2018-10-10 ./test1.txt[in file] ./test2.txt[out file]\n");
		return -1;
	}

	FILE* in = NULL;
	FILE* out = NULL;

	if (in = fopen(agrv[1], "rb")) {
		printf("open in file suceess\n");
	}
	else {
		printf("open in file failed!\n");
		return -2;
	}
	if (out = fopen(agrv[2], "wb")){
		printf("open out file suceess\n");
	}
	else {
		printf("open out file failed!\n");
		return -2;
	}

	char temp;
	char enter = '\r';
	char tab = '\t';
	char blank = ' ';

	while (1) {
		if (feof(in)) {
			printf("read to end\n");
			break;
		}
		fread(&temp, sizeof(char), 1, in);
		if (temp == enter) {
			continue;
		}
		if (temp == tab) {
			for (int i = 0; i < 4; i++) {
				fwrite(&blank, sizeof(char), 1, out);
			}
			continue;
		}	
		fwrite(&temp, sizeof(char), 1, out);
	}
	
	fclose(in);
	fclose(out);
	printf("bye!\n");
	return 0;
}