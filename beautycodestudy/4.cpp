#include<iostream>  
#include<cmath>  
#include<windows.h>  

static int PERIOD = 60 * 1000; //周期ms  
const int COUNT = 300;  //一个周期计算次数  
const double GAP_LINEAR = 100;  //线性函数时间间隔100ms  
const double PI = 3.1415926535898; //PI  
const double GAP = (double)PERIOD / COUNT; //周期函数时间间隔  
const double FACTOR = 2 * PI / PERIOD;  //周期函数的系数  
static double Ratio = 0.5;  //线性函数的值 0.5即50%  
static double Max = 0.9; //方波函数的最大值  
static double Min = 0.1; //方波函数的最小值  

typedef double Func(double);  //定义一个函数类型 Func*为函数指针  
typedef void Solve(Func *calc);//定义函数类型，参数为函数指针Func*  
inline DWORD get_time()
{
	return GetTickCount(); //操作系统启动到现在所经过的时间ms  
}
double calc_sin(double x)  //调用周期函数solve_period的参数  
{
	return (1 + sin(FACTOR * x)) / 2; //y=1/2(1+sin(a*x))  
}
double calc_fangbo(double x)  //调用周期函数solve_period的参数  
{
	//方波函数  
	if (x <= PERIOD / 2) return Max;
	else return Min;
}

void solve_period(Func *calc) //线程函数为周期函数  
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

void solve_linear(Func*)  //线程函数为线性函数，参数为空 NULL  
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
//void solve_nonperiod(Func *calc) //非周期函数的处理，暂没实验  
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
//i为输出状态，R为直线函数的值，T为周期函数的周期，max方波最大值，min方波最小值  
{
	Ratio = R; PERIOD = T; Max = max; Min = min;
	Func *func[] = { NULL, calc_sin, calc_fangbo };  //传给Solve的参数，函数指针数组  
	Solve *solve_func[] = { solve_linear, solve_period };  //Solve函数指针数组  
	const int NUM_CPUS = 4;  //双核，通用的可以用下面GetSystemInfo得到cpu数目  
	HANDLE handle[NUM_CPUS];
	DWORD thread_id[NUM_CPUS]; //线程id  
	SYSTEM_INFO info;  
	GetSystemInfo(&info);   //得到cpu数目  
	const int num = info.dwNumberOfProcessors;  
	printf("%d", num);
	switch (i)
	{
	case 1: //cpu1 ,cpu2都输出直线  
	{
		for (int i = 0; i < NUM_CPUS; ++i)
		{
			Func *calc = func[0];
			Solve *solve = solve_func[0];
			if ((handle[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve,
				(VOID*)calc, 0, &thread_id[i])) != NULL)  //创建新线程  
				SetThreadAffinityMask(handle[i], i + 1); //限定线程运行在哪个cpu上  
		}
		WaitForSingleObject(handle[0], INFINITE);   //等待线程结束  
		break;
	}
	case 2: //cpu1直线，cpu2正弦  
	{
		for (int i = 0; i < NUM_CPUS; ++i)
		{
			Func *calc = func[i];
			Solve *solve = solve_func[i];
			if ((handle[i] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve,
				(VOID*)calc, 0, &thread_id[i])) != NULL)  //创建新线程  
				SetThreadAffinityMask(handle[i], i + 1); //限定线程运行在哪个cpu上  
		}
		WaitForSingleObject(handle[0], INFINITE);   //等待线程结束  
		break;
	}
	case 3: //cpu1直线，cpu2方波  
	{

		/*Func *calc = func[0];
		Solve *solve = solve_func[0];*/
		if ((handle[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve_func[0],
			(VOID*)func[0], 0, &thread_id[0])) != NULL)  //创建新线程  
			SetThreadAffinityMask(handle[0], 1); //限定线程运行在哪个cpu上  
		Func *calc = func[2];
		Solve *solve = solve_func[1];
		if ((handle[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve,
			(VOID*)calc, 0, &thread_id[1])) != NULL)  //创建新线程  
			SetThreadAffinityMask(handle[1], 2); //限定线程运行在哪个cpu上  
		WaitForSingleObject(handle[0], INFINITE);   //等待线程结束  
		break;
	}
	case 4: //cpu1正弦，cpu2方波  
	{
		if ((handle[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve_func[1],
			(VOID*)func[1], 0, &thread_id[0])) != NULL)  //创建新线程  
			SetThreadAffinityMask(handle[0], 1); //限定线程运行在哪个cpu上  
		Func *calc = func[2];
		Solve *solve = solve_func[1];
		if ((handle[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)solve,
			(VOID*)calc, 0, &thread_id[1])) != NULL)  //创建新线程  
			SetThreadAffinityMask(handle[1], 2); //限定线程运行在哪个cpu上  
		WaitForSingleObject(handle[0], INFINITE);   //等待线程结束  
		break;
	}
	default: break;
	}
}

void main()
{
	run();  //cpu1 ,cpu2都输出50%的直线  
	//run(2,0.5,30000); //cpu1 0.5直线，cpu2正弦周期30000  
	//run(3);  //cpu1直线，cpu2方波  
	//run(4,0.8,30000,0.95,0.5); //cpu1正弦，cpu2 0.95-0.5的方波  
}