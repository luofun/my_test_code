#include<iostream>  
#include<cmath>  
#include<windows.h>  

static int PERIOD = 60 * 1000; //����ms  
const int COUNT = 300;  //һ�����ڼ������  
const double GAP_LINEAR = 100;  //���Ժ���ʱ����100ms  
const double PI = 3.1415926535898; //PI  
const double GAP = (double)PERIOD / COUNT; //���ں���ʱ����  
const double FACTOR = 2 * PI / PERIOD;  //���ں�����ϵ��  
static double Ratio = 0.5;  //���Ժ�����ֵ 0.5��50%  
static double Max = 0.9; //�������������ֵ  
static double Min = 0.1; //������������Сֵ  

typedef double Func(double);  //����һ���������� Func*Ϊ����ָ��  
typedef void Solve(Func *calc);//���庯�����ͣ�����Ϊ����ָ��Func*  
inline DWORD get_time()
{
	return GetTickCount(); //����ϵͳ������������������ʱ��ms  
}
double calc_sin(double x)  //�������ں���solve_period�Ĳ���  
{
	return (1 + sin(FACTOR * x)) / 2; //y=1/2(1+sin(a*x))  
}
double calc_fangbo(double x)  //�������ں���solve_period�Ĳ���  
{
	//��������  
	if (x <= PERIOD / 2) return Max;
	else return Min;
}

void solve_period(Func *calc) //�̺߳���Ϊ���ں���  
{
	double x = 0.0;
	double cache[COUNT];
	for (int i = 0; i < COUNT; ++i, x += GAP)
		cache[i] = calc(x);
	int count = 0;
	while (1)
	{
		unsigned ta = get_time();
		if (count >= COUNT) count = 0;
		double r = cache[count++];
		DWORD busy = r * GAP;
		while (get_time() - ta < busy) {}
		Sleep(GAP - busy);
	}
}

void solve_linear(Func*)  //�̺߳���Ϊ���Ժ���������Ϊ�� NULL  
{
	const unsigned BUSY = Ratio * GAP_LINEAR;
	const unsigned IDLE = (1 - Ratio) * GAP_LINEAR;
	while (1)
	{
		unsigned ta = get_time();
		while (get_time() - ta < BUSY) {}
		Sleep(IDLE);
	}
}
//void solve_nonperiod(Func *calc) //�����ں����Ĵ�����ûʵ��  
//{  
//  double tb = 0;  
//  while(1)  
//  {  
//    unsigned ta = get_time();  
//    double r = calc(tb);  
//    if (r < 0 || r > 1) r = 1;  
//    DWORD busy = r * GAP;  
//    while(get_time() - ta < busy) {}  
//    Sleep(GAP - busy);  
//    //tb += GAP;  
//    tb += get_time() - ta;  
//  }  
//}  

void run(int i = 1, double R = 0.5, double T = 60000, double max = 0.9, double min = 0.1)
//iΪ���״̬��RΪֱ�ߺ�����ֵ��TΪ���ں��������ڣ�max�������ֵ��min������Сֵ  
{
	Ratio = R; PERIOD = T; Max = max; Min = min;
	Func *func[] = { NULL, calc_sin, calc_fangbo };  //����Solve�Ĳ���������ָ������  
	Solve *solve_func[] = { solve_linear, solve_period };  //Solve����ָ������  
	const int NUM_CPUS = 4;  //˫�ˣ�ͨ�õĿ���������GetSystemInfo�õ�cpu��Ŀ  
	HANDLE handle[NUM_CPUS];
	DWORD thread_id[NUM_CPUS]; //�߳�id  
	SYSTEM_INFO info;  
	GetSystemInfo(&info);   //�õ�cpu��Ŀ  
	const int num = info.dwNumberOfProcessors;  
	printf("%d", num);
	switch (i)
	{
	case 1: //cpu1 ,cpu2�����ֱ��  
	{
		for (int i = 0; i < NUM_CPUS; ++i)
		{
			Func *calc = func[0];
			Solve *solve = solve_func[0];
			if ((handle[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve,
				(VOID*)calc, 0, &thread_id[i])) != NULL)  //�������߳�  
				SetThreadAffinityMask(handle[i], i + 1); //�޶��߳��������ĸ�cpu��  
		}
		WaitForSingleObject(handle[0], INFINITE);   //�ȴ��߳̽���  
		break;
	}
	case 2: //cpu1ֱ�ߣ�cpu2����  
	{
		for (int i = 0; i < NUM_CPUS; ++i)
		{
			Func *calc = func[i];
			Solve *solve = solve_func[i];
			if ((handle[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve,
				(VOID*)calc, 0, &thread_id[i])) != NULL)  //�������߳�  
				SetThreadAffinityMask(handle[i], i + 1); //�޶��߳��������ĸ�cpu��  
		}
		WaitForSingleObject(handle[0], INFINITE);   //�ȴ��߳̽���  
		break;
	}
	case 3: //cpu1ֱ�ߣ�cpu2����  
	{

		/*Func *calc = func[0];
		Solve *solve = solve_func[0];*/
		if ((handle[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve_func[0],
			(VOID*)func[0], 0, &thread_id[0])) != NULL)  //�������߳�  
			SetThreadAffinityMask(handle[0], 1); //�޶��߳��������ĸ�cpu��  
		Func *calc = func[2];
		Solve *solve = solve_func[1];
		if ((handle[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve,
			(VOID*)calc, 0, &thread_id[1])) != NULL)  //�������߳�  
			SetThreadAffinityMask(handle[1], 2); //�޶��߳��������ĸ�cpu��  
		WaitForSingleObject(handle[0], INFINITE);   //�ȴ��߳̽���  
		break;
	}
	case 4: //cpu1���ң�cpu2����  
	{
		if ((handle[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve_func[1],
			(VOID*)func[1], 0, &thread_id[0])) != NULL)  //�������߳�  
			SetThreadAffinityMask(handle[0], 1); //�޶��߳��������ĸ�cpu��  
		Func *calc = func[2];
		Solve *solve = solve_func[1];
		if ((handle[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve,
			(VOID*)calc, 0, &thread_id[1])) != NULL)  //�������߳�  
			SetThreadAffinityMask(handle[1], 2); //�޶��߳��������ĸ�cpu��  
		WaitForSingleObject(handle[0], INFINITE);   //�ȴ��߳̽���  
		break;
	}
	default: break;
	}
}

void main()
{
	run();  //cpu1 ,cpu2�����50%��ֱ��  
	//run(2,0.5,30000); //cpu1 0.5ֱ�ߣ�cpu2��������30000  
	//run(3);  //cpu1ֱ�ߣ�cpu2����  
	//run(4,0.8,30000,0.95,0.5); //cpu1���ң�cpu2 0.95-0.5�ķ���  
}