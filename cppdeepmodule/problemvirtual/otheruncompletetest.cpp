#include<iostream>

using namespace std;


class B
{
public:
	int ib;
	char cb;
public:
	B() :ib(0), cb('B') {}

	virtual void f() { cout << "B::f()" << endl; }
	virtual void Bf() { cout << "B::Bf()" << endl; }
};

class Bv1 : virtual public B{
public:
	int ib1;
	char cb1;
public:
	Bv1() :ib1(11), cb1('1') {}

	virtual void f() { cout << "Bv1::f()" << endl; }
	//virtual void f1() { cout << "Bv1::f1()" << endl; }
	//virtual void Bf1() { cout << "Bv1::Bf1()" << endl; }
};

class Bv2 : virtual public B{
public:
	int ib2;
	char cb2;
public:
	Bv2() :ib2(12), cb2('2') {}

	virtual void f() { cout << "Bv2::f()" << endl; }
	virtual void f2() { cout << "Bv2::f2()" << endl; }
	virtual void Bf2() { cout << "Bv2::Bf2()" << endl; }
};

class Dv : public Bv1, public Bv2{
public:
	int id;
	char cd;
public:
	Dv() :id(100), cd('D') {}

	virtual void f() { cout << "Dv::f()" << endl; }
	virtual void f1() { cout << "Dv::f1()" << endl; }
	virtual void f2() { cout << "Dv::f2()" << endl; }
	virtual void Df() { cout << "Dv::Df()" << endl; }
};

typedef void(*Fun)(void);

int main(int argc, char* argv[])
{
	Bv1 bb1;
	Fun pFun = NULL;
	int** pVtab = NULL;

	pVtab = (int**)&bb1;
	/*cout << "[0] Bv1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];
	cout << "     [0] ";
	pFun(); //Bv1::f1();
	cout << "     [1] ";
	pFun = (Fun)pVtab[0][1];
	pFun(); //Bv1::bf1();
	cout << "     [2] ";
	cout << pVtab[0][2] << endl;*/

	cout << "[1] = 0x";
	cout << (int*)*((int*)(&bb1) + 0) << endl; //Bv1::ib1
	cout << *(int*)*((int*)(&bb1) + 0) << endl; //*Bv1::ib1
	cout << "[2] Bv1::ib1 = ";
	cout << (int)*((int*)(&bb1) + 2) << endl; //Bv1::ib1
	cout << "[3] Bv1::cb1 = ";
	cout << (char)*((int*)(&bb1) + 3) << endl; //Bv1::cb1

	cout << "[4] = 0x";
	cout << (int*)*((int*)(&bb1) + 4) << endl; //NULL

	cout << "[5] B::_vptr->" << endl;
	cout << "     [0] ";
	pFun = (Fun)pVtab[5][0];
	pFun(); //Bv1::f();
	pFun = (Fun)pVtab[5][1];
	cout << "     [1] ";
	pFun(); //B::Bf();
	cout << "     [2] ";
	cout << "0x" << (Fun)pVtab[5][2] << endl;

	cout << "[6] B::ib = ";
	cout << (int)*((int*)(&bb1) + 6) << endl; //B::ib
	cout << "[7] B::cb = ";
	cout << (char)*((int*)(&bb1) + 7) << endl; //B::cb


	return 0;
}