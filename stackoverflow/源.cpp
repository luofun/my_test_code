#include<stdio.h>
//#define stackoverflow
//#define duiduidui

//int goaltest[100000000] = { 0 };///no problem here

void death(void)
{
	death();
};

int main(int argc,char* argv[])
{
	printf("\n\n\na long time test\n\n\n");

	#ifdef stackoverflow
	printf("\n\nrady to death\n\n");
	int over[100000000]={0};
	#endif

	#ifdef duiduidui
	printf("\n\ndui work\n\n");
	int *work=new int[100000000];
	delete[] work;
	#endif

	death();


	return 0;
}