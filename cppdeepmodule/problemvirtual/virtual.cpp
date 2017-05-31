//#include<stdio.h>
//#pragma pack(1)
#include<iostream>

using namespace std;

class Base {
public:
	virtual void f() { cout << "Base::f" << endl; }
	virtual void g() { cout << "Base::g" << endl; }
	virtual void h() { cout << "Base::h" << endl; }

};

class Base1 {
public:
	virtual void f() { cout << "Base1::f" << endl; }
	virtual void g() { cout << "Base1::g" << endl; }
	virtual void h() { cout << "Base1::h" << endl; }

};

class Base2 {
public:
	virtual void f() { cout << "Base2::f" << endl; }
	virtual void g() { cout << "Base2::g" << endl; }
	virtual void h() { cout << "Base2::h" << endl; }

};

class Base3 {
public:
	virtual void f() { cout << "Base3::f" << endl; }
	virtual void g() { cout << "Base3::g" << endl; }
	virtual void h() { cout << "Base3::h" << endl; }

};

class D1 : public Base
{
public:
	virtual void f1() { cout << "D1::f1" << endl; }
	virtual void g1() { cout << "D1::g1" << endl; }
	virtual void h1() { cout << "D1::h1" << endl; }

};

class D2 :public Base
{
public:
	virtual void f() { cout << "D2::f" << endl; }
	virtual void g1() { cout << "D2::g1" << endl; }
	virtual void h1() { cout << "D2::h1" << endl; }
};

class D3 :public Base1, public Base2, public Base3
{
public:
	virtual void f1() { cout << "D3::f1" << endl; }
	virtual void g1() { cout << "D3::g1" << endl; }
	virtual void h1() { cout << "D3::h1" << endl; }

};

class D4 :public Base1, public Base2, public Base3
{
public:
	virtual void f() { cout << "D4::f" << endl; }
	virtual void g1() { cout << "D4::g1" << endl; }
	virtual void h1() { cout << "D4::h1" << endl; }

};

class Basep {
private:
	virtual void f() { cout << "Base::f private function" << endl; }

};

class Dp : public Basep{

};

class Parent {
public:
	int iparent;
	Parent() :iparent(10) {}
	virtual void f() { cout << " Parent::f()" << endl; }
	virtual void g() { cout << " Parent::g()" << endl; }
	virtual void h() { cout << " Parent::h()" << endl; }

};

class Child : public Parent {
public:
	int ichild;
	Child() :ichild(100) {}
	virtual void f() { cout << "Child::f()" << endl; }
	virtual void g_child() { cout << "Child::g_child()" << endl; }
	virtual void h_child() { cout << "Child::h_child()" << endl; }
};

class GrandChild : public Child{
public:
	int igrandchild;
	GrandChild() :igrandchild(1000) {}
	virtual void f() { cout << "GrandChild::f()" << endl; }
	virtual void g_child() { cout << "GrandChild::g_child()" << endl; }
	virtual void h_grandchild() { cout << "GrandChild::h_grandchild()" << endl; }
};

class Basen1 {
public:
	int ibase1;
	Basen1() :ibase1(10) {}
	virtual void f() { cout << "Basen1::f()" << endl; }
	virtual void g() { cout << "Basen1::g()" << endl; }
	virtual void h() { cout << "Basen1::h()" << endl; }

};

class Basen2 {
public:
	int ibase2;
	Basen2() :ibase2(20) {}
	virtual void f() { cout << "Basen2::f()" << endl; }
	virtual void g() { cout << "Basen2::g()" << endl; }
	virtual void h() { cout << "Basen2::h()" << endl; }
};

class Basen3 {
public:
	int ibase3;
	Basen3() :ibase3(30) {}
	virtual void f() { cout << "Basen3::f()" << endl; }
	virtual void g() { cout << "Basen3::g()" << endl; }
	virtual void h() { cout << "Basen3::h()" << endl; }
};


class Dn1 : public Basen1, public Basen2, public Basen3 {
public:
	int iderive;
	Dn1() :iderive(100) {}
	virtual void f() { cout << "Derive::f()" << endl; }
	virtual void g1() { cout << "Derive::g1()" << endl; }
};

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
class B1 : public B
{
public:
	int ib1;
	char cb1;
public:
	B1() :ib1(11), cb1('1') {}

	virtual void f() { cout << "B1::f()" << endl; }
	virtual void f1() { cout << "B1::f1()" << endl; }
	virtual void Bf1() { cout << "B1::Bf1()" << endl; }

};
class B2 : public B
{
public:
	int ib2;
	char cb2;
public:
	B2() :ib2(12), cb2('2') {}

	virtual void f() { cout << "B2::f()" << endl; }
	virtual void f2() { cout << "B2::f2()" << endl; }
	virtual void Bf2() { cout << "B2::Bf2()" << endl; }

};

class D : public B1, public B2
{
public:
	int id;
	char cd;
public:
	D() :id(100), cd('D') {}

	virtual void f() { cout << "D::f()" << endl; }
	virtual void f1() { cout << "D::f1()" << endl; }
	virtual void f2() { cout << "D::f2()" << endl; }
	virtual void Df() { cout << "D::Df()" << endl; }

};

class Bv1 : virtual public B{
public:
	int ib1;
	char cb1;
public:
	Bv1() :ib1(11), cb1('1') {}

	virtual void f() { cout << "Bv1::f()" << endl; }
	virtual void f1() { cout << "Bv1::f1()" << endl; }
	virtual void Bf1() { cout << "Bv1::Bf1()" << endl; }
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

int main(int argc, char* aryv[])
{
	typedef void(*Fun)(void);//fun 函数别名

	Base b;
	D1 d;
	D2 dd;
	D3 ddd;
	D4 dddd;
	Dp dp;
	Base1 *bp1;

	Fun pFun = NULL;

	cout << "虚函数表地址：" << (int*)(&b) << endl;
	cout << "虚函数表 — 第一个函数地址：" << (int*)*(int*)(&b) << endl; //*(int*)(&b)地址值

	// Invoke the first virtual function 
	pFun = (Fun)*((int*)*(int*)(&b));
	pFun();
	pFun = (Fun)*((int*)*(int*)(&b) + 0);  // Base::f()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&b) + 1);  // Base::g()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&b) + 2);  // Base::h()
	pFun();

	cout << "子类D1虚函数表地址：" << (int*)(&d) << endl;
	cout << "子类D1虚函数表 — 第一个函数地址：" << (int*)*(int*)(&d) << endl; //*(int*)(&d)地址值

	pFun = (Fun)*((int*)*(int*)(&d) + 0);  // Base::f()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d) + 1);  // Base::g()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d) + 2);  // Base::h()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d) + 3);  // D1::f1()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d) + 4);  // D1::g1()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&d) + 5);  // D1::h1()
	pFun();

	cout << "子类D2虚函数表地址：" << (int*)(&dd) << endl;
	cout << "子类D2虚函数表 — 第一个函数地址：" << (int*)*(int*)(&dd) << endl; //*(int*)(&d)地址值

	pFun = (Fun)*((int*)*(int*)(&dd) + 0);  // D2::f()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&dd) + 1);  // Base::g()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&dd) + 2);  // Base::h()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&dd) + 3);  // D2::g1()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&dd) + 4);  // D2::h1()
	pFun();

	cout << "子类D3虚函数表地址：" << (int*)(&ddd) << endl;
	cout << "子类D3虚函数表 — 第一个函数地址：" << (int*)*(int*)(&ddd) << endl; //*(int*)(&d)地址值

	pFun = (Fun)*((int*)*(int*)(&ddd) + 0);  // Base1::f()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&ddd) + 1);  // Base1::g()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&ddd) + 2);  // Base1::h()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&ddd) + 3);  // D3::f1()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&ddd) + 4);  // D3::g1()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&ddd) + 5);  // D3::h1()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&ddd) + 1) + 0);  // Base2::f()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&ddd) + 1) + 1);  // Base2::g()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&ddd) + 1) + 2);  // Base2::h()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&ddd) + 2) + 0);  // Base3::f()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&ddd) + 2) + 1);  // Base3::g()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&ddd) + 2) + 2);  // Base3::h()
	pFun();

	cout << "子类D4虚函数表地址：" << (int*)(&dddd) << endl;
	cout << "子类D4虚函数表 — 第一个函数地址：" << (int*)*(int*)(&dddd) << endl; //*(int*)(&d)地址值
	pFun = (Fun)*((int*)*(int*)(&dddd) + 0);  // D4::f()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&dddd) + 1);  // Base1::g()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&dddd) + 2);  // Base1::h()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&dddd) + 3);  // D4::g1()
	pFun();
	pFun = (Fun)*((int*)*(int*)(&dddd) + 4);  // D4::h1()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&dddd) + 1) + 0);  // D4::f()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&dddd) + 1) + 1);  // Base2::g()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&dddd) + 1) + 2);  // Base2::h()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&dddd) + 2) + 0);  // D4::f()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&dddd) + 2) + 1);  // Base3::g()
	pFun();
	pFun = (Fun)*((int*)*((int*)(&dddd) + 2) + 2);  // Base3::h()
	pFun();
	
	pFun = (Fun)*((int*)*(int*)(&dp) + 0);//private fun test
	pFun();

	bp1 = new D3();
	pFun = (Fun)*((int*)*(int*)bp1 + 0);  // Base1::f() father use son
	pFun();
	pFun = (Fun)*((int*)*(int*)bp1 + 3);  // D3::f1() father use son
	pFun();

	delete bp1;


	GrandChild gc;


	int** pVtab = (int**)&gc;

	cout << "[0] GrandChild::_vptr->" << endl;
	for (int i = 0; (Fun)pVtab[0][i] != NULL; i++){
		pFun = (Fun)pVtab[0][i];
		cout << "    [" << i << "] ";
		pFun();
	}
	cout << "[1] Parent.iparent = " << (int)pVtab[1] << endl;
	cout << "[2] Child.ichild = " << (int)pVtab[2] << endl;
	cout << "[3] GrandChild.igrandchild = " << (int)pVtab[3] << endl;

	Dn1 dn;

	pVtab = (int**)&dn;

	cout << "[0] Base1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];
	cout << "     [0] ";
	pFun();

	pFun = (Fun)pVtab[0][1];
	cout << "     [1] "; pFun();

	pFun = (Fun)pVtab[0][2];
	cout << "     [2] "; pFun();

	pFun = (Fun)pVtab[0][3];
	cout << "     [3] "; pFun();

	pFun = (Fun)pVtab[0][4];
	cout << "     [4] "; cout << pFun << endl;

	cout << "[1] Base1.ibase1 = " << (int)pVtab[1] << endl;


	int s = sizeof(Basen1) / 4;

	cout << "[" << s << "] Base2::_vptr->" << endl;
	pFun = (Fun)pVtab[s][0];
	cout << "     [0] "; pFun();

	pFun = (Fun)pVtab[s][1];
	cout << "     [1] "; pFun();

	pFun = (Fun)pVtab[s][2];
	cout << "     [2] "; pFun();

	pFun = (Fun)pVtab[s][3];
	cout << "     [3] ";
	cout << pFun << endl;

	cout << "[" << s + 1 << "] Base2.ibase2 = " << (int)pVtab[s + 1] << endl;

	s = s + sizeof(Basen2) / 4;

	cout << "[" << s << "] Base3::_vptr->" << endl;
	pFun = (Fun)pVtab[s][0];
	cout << "     [0] "; pFun();

	pFun = (Fun)pVtab[s][1];
	cout << "     [1] "; pFun();

	pFun = (Fun)pVtab[s][2];
	cout << "     [2] "; pFun();

	pFun = (Fun)pVtab[s][3];
	cout << "     [3] ";
	cout << pFun << endl;

	s++;
	cout << "[" << s << "] Base3.ibase3 = " << (int)pVtab[s] << endl;
	s++;
	cout << "[" << s << "] Derive.iderive = " << (int)pVtab[s] << endl;

	D d0;
	pVtab = (int**)&d0;
	cout << "[0] D::B1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];
	cout << "     [0] ";    pFun();
	pFun = (Fun)pVtab[0][1];
	cout << "     [1] ";    pFun();
	pFun = (Fun)pVtab[0][2];
	cout << "     [2] ";    pFun();
	pFun = (Fun)pVtab[0][3];
	cout << "     [3] ";    pFun();
	pFun = (Fun)pVtab[0][4];
	cout << "     [4] ";    pFun();
	pFun = (Fun)pVtab[0][5];
	cout << "     [5] 0x" << pFun << endl;

	cout << "[1] B::ib = " << (int)pVtab[1] << endl;
	cout << "[2] B::cb = " << (char)pVtab[2] << endl;
	cout << "[3] B1::ib1 = " << (int)pVtab[3] << endl;
	cout << "[4] B1::cb1 = " << (char)pVtab[4] << endl;

	cout << "[5] D::B2::_vptr->" << endl;
	pFun = (Fun)pVtab[5][0];
	cout << "     [0] ";    pFun();
	pFun = (Fun)pVtab[5][1];
	cout << "     [1] ";    pFun();
	pFun = (Fun)pVtab[5][2];
	cout << "     [2] ";    pFun();
	pFun = (Fun)pVtab[5][3];
	cout << "     [3] ";    pFun();
	pFun = (Fun)pVtab[5][4];
	cout << "     [4] 0x" << pFun << endl;

	cout << "[6] B::ib = " << (int)pVtab[6] << endl;
	cout << "[7] B::cb = " << (char)pVtab[7] << endl;
	cout << "[8] B2::ib2 = " << (int)pVtab[8] << endl;
	cout << "[9] B2::cb2 = " << (char)pVtab[9] << endl;

	cout << "[10] D::id = " << (int)pVtab[10] << endl;
	cout << "[11] D::cd = " << (char)pVtab[11] << endl;

	Bv1 bb1;

	pVtab = (int**)&bb1;
	cout << "[0] Bv1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];
	cout << "     [0] ";
	pFun(); //Bv1::f1();
	cout << "     [1] ";
	pFun = (Fun)pVtab[0][1];
	pFun(); //Bv1::bf1();
	cout << "     [2] ";
	cout << pVtab[0][2] << endl;

	cout << "[1] = 0x";
	cout << (int*)*((int*)(&bb1) + 1) << endl; //Bv1::ib1
	cout << *(int*)*((int*)(&bb1) + 1) << endl; //*Bv1::ib1
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

	Dv dv;

	pVtab = (int**)&dv;
	cout << "[0] D::B1::_vptr->" << endl;
	pFun = (Fun)pVtab[0][0];
	cout << "     [0] ";    pFun(); //D::f1();
	pFun = (Fun)pVtab[0][1];
	cout << "     [1] ";    pFun(); //B1::Bf1();
	pFun = (Fun)pVtab[0][2];
	cout << "     [2] ";    pFun(); //D::Df();
	pFun = (Fun)pVtab[0][3];
	cout << "     [3] ";
	cout << pFun << endl;

	//cout << pVtab[4][2] << endl;
	cout << "[1] = 0x";
	cout << (int*)((&dv) + 1) << endl; //????
	cout << *(int*)*((int*)(&dv) + 1) << endl; 

	cout << "[2] B1::ib1 = ";
	cout << *((int*)(&dv) + 2) << endl; //B1::ib1
	cout << "[3] B1::cb1 = ";
	cout << (char)*((int*)(&dv) + 3) << endl; //B1::cb1

	//---------------------
	cout << "[4] D::B2::_vptr->" << endl;
	pFun = (Fun)pVtab[4][0];
	cout << "     [0] ";    pFun(); //D::f2();
	pFun = (Fun)pVtab[4][1];
	cout << "     [1] ";    pFun(); //B2::Bf2();
	pFun = (Fun)pVtab[4][2];
	cout << "     [2] ";
	cout << pFun << endl;

	cout << "[5] = 0x";
	cout << *((int*)(&dv) + 5) << endl; // ???
	cout << *(int*)*((int*)(&dv) + 5) << endl;

	cout << "[6] B2::ib2 = ";
	cout << (int)*((int*)(&dv) + 6) << endl; //B2::ib2
	cout << "[7] B2::cb2 = ";
	cout << (char)*((int*)(&dv) + 7) << endl; //B2::cb2

	cout << "[8] D::id = ";
	cout << *((int*)(&dv) + 8) << endl; //D::id
	cout << "[9] D::cd = ";
	cout << (char)*((int*)(&dv) + 9) << endl;//D::cd

	cout << "[10]  = 0x";
	cout << (int*)*((int*)(&dv) + 10) << endl;
	//---------------------
	cout << "[11] D::B::_vptr->" << endl;
	cout << "     [0] ";  //D::f();
	pFun = (Fun)pVtab[11][0];
	pFun();
	pFun = (Fun)pVtab[11][1];
	cout << "     [1] "; //B::Bf();
	pFun();
	pFun = (Fun)pVtab[11][2];
	cout << "     [2] ";
	cout << pFun << endl;

	cout << "[12] B::ib = ";
	cout << *((int*)(&dv) + 12) << endl; //B::ib
	cout << "[13] B::cb = ";
	cout << (char)*((int*)(&dv) + 13) << endl;//B::cb

	return 0;
}