///testuse60
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void in2outstr1(char* out, char* in, int size) {
	int i = 0;
	int j = 0;

	for (i = 3; i < 11; i++)
	{

		out[i] = in[j];
		j++;
	}

	for (i = 14; i < 18; i++)
	{
		out[i] = in[j];
		j++;
	}

	for (i = 21; i < 25; i++)
	{
		out[i] = in[j];
		j++;
	}

	for (i = 29; i < 31; i++)
	{
		out[i] = in[j];
		j++;
	}

	for (i = 34; i < 36; i++)
	{
		out[i] = in[j];
		j++;
	}

	for (i = 39; i < 41; i++)
	{
		out[i] = in[j];
		j++;
	}

	for (i = 44; i < 46; i++)
	{
		out[i] = in[j];
		j++;
	}

	for (i = 49; i < 51; i++)
	{
		out[i] = in[j];
		j++;
	}

	for (i = 54; i < 56; i++)
	{
		out[i] = in[j];
		j++;
	}

	for (i = 59; i < 61; i++)
	{
		out[i] = in[j];
		j++;
	}

	for (i = 64; i < 66; i++)
	{
		out[i] = in[j];
		j++;
	}
}

void in2outstr2(char* out, char* in, int size) {
	int i = 0;
	int j = 0;

	for (i = 0; i < 8; i++)
	{
		out[i] = in[j];
		j++;
	}
	for (i = 9; i < 13; i++)
	{
		out[i] = in[j];
		j++;
	}
	for (i = 14; i < 18; i++)
	{
		out[i] = in[j];
		j++;
	}
	for (i = 19; i < 23; i++)
	{
		out[i] = in[j];
		j++;
	}
	for (i = 24; i < 36; i++)
	{
		out[i] = in[j];
		j++;
	}
}

int set1(char* outstrstyle1, int needsize) {
	FILE* fp;
	fp = fopen("guid1.txt", "wt");
	int** numvalue;
	char** numcharstr;
	int sign = 32;

	numcharstr = (char**)malloc(sizeof(char*)*needsize);
	numvalue = (int**)malloc(sizeof(int*)*needsize);

	for (int i = 0; i < needsize; i++)
	{
		numcharstr[i] = (char*)malloc(sizeof(char) * 32 + 1);
		numvalue[i] = (int*)malloc(sizeof(int) * 32);
	}

	for (int i = 0; i < needsize; i++)
	{
		for (int j = 0; j < sign; j++)
		{
			numvalue[i][j] = rand() % 16;
		}
	}

	for (int i = 0; i < needsize; i++)
	{
		for (int j = 0; j < sign; j++)
		{
			sprintf(&numcharstr[i][j], "%X", numvalue[i][j]);
		}

		if (i > 0)
		{
			for (int k = 0; k < i; k++)
			{
				if (strcmp(numcharstr[k], numcharstr[i]) == 0)
				{
					printf("\ntwo same guid\ntry again\n\n");

					fprintf(fp, "try again\n");

					fclose(fp);
					for (int i = 0; i < needsize; i++)
					{
						free(numvalue[i]);
						free(numcharstr[i]);
					}
					free(numvalue);
					free(numcharstr);

					return 1;
				}
			}
		}
	}

	for (int i = 0; i < needsize; i++) {
		in2outstr1(outstrstyle1, numcharstr[i], sign);
		fprintf(fp, "%s\n", outstrstyle1);
		printf("%s\n", outstrstyle1);
	}

	for (int i = 0; i < needsize; i++)
	{
		free(numvalue[i]);
		free(numcharstr[i]);
	}
	free(numvalue);
	free(numcharstr);
	fclose(fp);
	printf("\nsee the file(guid1.txt)\n\n");
	return 0;
}

int set2(char* outstrstyle2, int needsize) {
	FILE* fp;
	fp = fopen("guid2.txt", "wt");
	int** numvalue;
	char** numcharstr;
	int sign = 32;

	numcharstr = (char**)malloc(sizeof(char*)*needsize);
	numvalue = (int**)malloc(sizeof(int*)*needsize);

	for (int i = 0; i < needsize; i++)
	{
		numcharstr[i] = (char*)malloc(sizeof(char) * 32 + 1);
		numvalue[i] = (int*)malloc(sizeof(int) * 32);
	}

	for (int i = 0; i < needsize; i++)
	{
		for (int j = 0; j < sign; j++)
		{
			numvalue[i][j] = rand() % 16;
		}
	}

	for (int i = 0; i < needsize; i++)
	{
		for (int j = 0; j < sign; j++)
		{
			sprintf(&numcharstr[i][j], "%X", numvalue[i][j]);
		}

		if (i > 0)
		{
			for (int k = 0; k < i; k++)
			{
				if (strcmp(numcharstr[k], numcharstr[i]) == 0)
				{
					printf("\ntwo same guid\ntry again\n\n");

					fprintf(fp, "try again\n");

					fclose(fp);
					for (int i = 0; i < needsize; i++)
					{
						free(numvalue[i]);
						free(numcharstr[i]);
					}
					free(numvalue);
					free(numcharstr);

					return 1;
				}
			}
		}
	}

	for (int i = 0; i < needsize; i++) {
		in2outstr2(outstrstyle2, numcharstr[i], sign);
		fprintf(fp, "%s\n", outstrstyle2);
		printf("%s\n", outstrstyle2);
	}

	for (int i = 0; i < needsize; i++)
	{
		free(numvalue[i]);
		free(numcharstr[i]);
	}
	free(numvalue);
	free(numcharstr);
	fclose(fp);
	printf("\nsee the file(guid2.txt)\n\n");
	return 0;
}



void main() {
	char outstrstyle1[] = "{0x________,0x____,0x____,{0x__,0x__,0x__,0x__,0x__,0x__,0x__,0x__}}";
	char outstrstyle2[] = "________-____-____-____-____________";
	int chooseone = -1;
	int needsize = 0;

	srand(time(NULL));

	printf("what kind of guid you need?\n1: %s\n2: %s\ninput your choose: ", outstrstyle1, outstrstyle2);
	scanf("%d", &chooseone);
	printf("how many guid you need? :\t");
	scanf("%d", &needsize);
	if (chooseone == 1)
		set1(outstrstyle1, needsize);
	if (chooseone == 2)
		set2(outstrstyle2, needsize);
	//system("pause");
}
///end
