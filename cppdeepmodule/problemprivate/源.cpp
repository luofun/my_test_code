#include<iostream>

using namespace std;

class test
{
private:
	int testi3;
public:
	int testi1;
	int testi2;
	test();
	~test();


};

test::test()
{
	this->testi1 = 1;
	this->testi2 = 2;
	this->testi3 = 3;
}

test::~test()
{

}

int main(int argc, char* argv[])
{
	test t1;
	int x = 0;

	cout << "ÀàµØÖ·£º" << (int*)(&t1) << endl;
	
	cout << "frist value test=" << '\t' << *(int*)((int*)(&t1) + 0) << endl;

	cout << "second value test=" << '\t' << *(int*)((int*)(&t1) + 1) << endl;

	cout << "thrid value test=" << '\t' << *(int*)((int*)(&t1) + 2) << endl;
	
	return 0;
}
