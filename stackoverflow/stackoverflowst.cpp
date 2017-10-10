// cpptest.cpp: 定义控制台应用程序的入口点。
//

#define FLOATING

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#include<Windows.h>
using namespace std;

int test1()
{
	string s("Somewhere down the road");
	istringstream iss(s);

	do
	{
		string subs;
		iss >> subs;
		cout << "Substring: " << subs << endl;
	} while (iss);

	return 0;
}



int test2() {
	string sentence = "And I feel fine...";
	istringstream iss(sentence);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		ostream_iterator<string>(cout, "\n"));
	return 0;
}

int test3(unsigned int x) {
	//bit operator
	unsigned int number=0;
	unsigned int bit;
	unsigned int n;
	
	number |= 1 << x;//Setting a bit
					 
	number &= ~(1 << x);//Clearing a bit

	number ^= 1 << x;//Toggling a bit

	bit = (number >> x) & 1;//Checking a bit

	//number ^= (-x ^ number) & (1 << n);//Changing the nth bit to x

	return 0;
}

int test4() {

	//double start = omp_get_wtime();

	const float x[16] = { 1.1,1.2,1.3,1.4,1.5,1.6,1.7,1.8,1.9,2.0,2.1,2.2,2.3,2.4,2.5,2.6 };
	const float z[16] = { 1.123,1.234,1.345,156.467,1.578,1.689,1.790,1.812,1.923,2.034,2.145,2.256,2.367,2.478,2.589,2.690 };
	float y[16];
	for (int i = 0; i < 16; i++)
	{
		y[i] = x[i];
	}
	for (int j = 0; j < 9000000; j++)
	{
		for (int i = 0; i < 16; i++)
		{
			y[i] *= x[i];
			y[i] /= z[i];
#ifdef FLOATING
			y[i] = y[i] + 0.1f;
			y[i] = y[i] - 0.1f;
#else
			y[i] = y[i] + 0;
			y[i] = y[i] - 0;
#endif

			if (j > 10000)
				cout << y[i] << "  ";
		}
		if (j > 10000)
			cout << endl;
	}

	//double end = omp_get_wtime();
	//cout << end - start << endl;

	system("pause");
	return 0;
}

namespace aaa {
	int xxx = 10;

}

int test5() {
	std::cout << aaa::xxx << endl;
	return 0;
}

int test6() {

	return 0;
}


int main() {
	test5();

	return 0;
}

