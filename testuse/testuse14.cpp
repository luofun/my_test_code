#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

void in2outstr(char* out, char* in, int size) {
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

int main() {
	srand(time(NULL));
	int ttt = 0;
	char outstrstyle[]= "{0x________,0x____,0x____,{0x__,0x__,0x__,0x__,0x__,0x__,0x__,0x__}}";
	int** numvalue;
	char** numcharstr;
	int sign = 32;
	FILE* fp;
	int needsize = 0;

	printf("how many guid you need? :\t");

	scanf("%d", &needsize);

	fp = fopen("guid.txt", "wt");

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
			sprintf(&numcharstr[i][j], "%x", numvalue[i][j]);
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

	putchar('\n');

	for (int i = 0; i < needsize; i++) {
		in2outstr(outstrstyle, numcharstr[i], sign);
		fprintf(fp, "%s\n", outstrstyle);
		printf("%s\n", outstrstyle);
	}

	fclose(fp);
	for (int i = 0; i < needsize; i++)
	{
		free(numvalue[i]);
		free(numcharstr[i]);
	}
	free(numvalue);
	free(numcharstr);

	printf("\nsee the file(guid.txt)\n\n");

	return 0;
}