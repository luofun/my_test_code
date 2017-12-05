///testuse56
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<string>
//#include<cstring>

int findlen(FILE* fp) {
	if (fp == NULL)
		return -1;
	int len = 0;
	char now = 0;
	while (!feof(fp) && now != '\n')
	{
		fread(&now, sizeof(now), 1, fp);
		len++;
	}
	fseek(fp, -len, SEEK_CUR);
	return len;
}

int onelen(FILE* fp) {
	if (fp == NULL)
		return -1;
	int len = 0;
	char now = 0;
	while (!feof(fp))
	{
		len++;
		fread(&now, sizeof(now), 1, fp);
		if (now == '\"')
		{
			while (!feof(fp) && now != '\"')
			{
				len++;
				fread(&now, sizeof(now), 1, fp);
			}
		}
		if (now == '\n' || now == ',')
			break;
	}
	fseek(fp, -len, SEEK_CUR);
	return len;
}

void readtheinidata() {

	
}


void main() {
	FILE *incsv, *outcpp;
	//FILE *inidatafile;
	//FILE *definefile;

	incsv = fopen("testexcel.csv", "rt");
	if (incsv == NULL)
	{
		printf("********************************\n\tOpen Csv File Erorr!\n********************************\n");
		system("pause");
		return;
	}

	/*
	inidatafile = fopen("test.ini", "rt");
	if (inidatafile == NULL)
	{
		printf("********************************\n\tOpen Ini File Erorr!\n********************************\n");
		system("pause");
		return;
	}
	*/

	outcpp = fopen("test.cpp", "wt");
	if (outcpp == NULL)
	{
		printf("********************************\n\tCreate File Erorr!\n********************************\n");
		system("pause");
		return;
	}

	
	std::string outstr = "GLOBAL_REMOVE_IF_UNREFERENCED GPIO_INIT_CONFIG mGpioTableDefault[] =\n{\n";
	
	std::string cccnum = "";
	int gpnum = 0;
	int tttlen = onelen(incsv);
	fseek(incsv, tttlen, SEEK_CUR);
	tttlen = onelen(incsv);
	cccnum.resize(tttlen - 1);
	char* tempcstr = (char*)malloc(sizeof(char)*(tttlen - 1));
	fread(tempcstr, sizeof(char), tttlen - 1, incsv);
	gpnum = atoi(tempcstr);
	rewind(incsv);

	int firstline = findlen(incsv);
	fseek(incsv, firstline, SEEK_CUR);

	int secondline = findlen(incsv);
	fseek(incsv, secondline, SEEK_CUR);
	
	for (int x = 0; x < gpnum; x++)
	{

		int linelen = findlen(incsv);
		fseek(incsv, -1, SEEK_CUR);
		
		int tdtime = 0;
		outstr += "{";

		for (int readnum = 0; readnum < linelen; readnum++)
		{
			char xxxnow;
			fread(&xxxnow, sizeof(char), 1, incsv);
			if (xxxnow == ',')
			{
			
				tdtime++;
			}
			
			if (tdtime == 2)
			{
				tdtime++;
				continue;
				
			}
			outstr.push_back(xxxnow);
			
			if (tdtime == 1)
			{
				outstr += "{";
			}
		}
		outstr.pop_back();
		outstr += "}},\n";
	}


	outstr += "\n};\n";

	fwrite(outstr.c_str(), sizeof(char), outstr.length(), outcpp);
	
	fclose(incsv);
	fclose(outcpp);
	//fclose(inidatafile);
	system("pause");
}