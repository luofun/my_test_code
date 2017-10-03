/*
把一摞饼按照大小次序摆好——从小到大，小在上，大在下
只能用一只手，一次抓住最上面的几块饼，把他们上下颠倒个个儿，
反复几次之后，排好序
假设有n块大小不一的烙饼，最少翻转几次，才能达到大小有序的结果？
*/
#include <iostream>  
#include <algorithm>  
#include <vector>  
using namespace std;
int T = 0;
void printData(int val)
{
	cout << val << " ";
}
void init_bin(vector<int> &v)
{
	int n;//需要排序的饼的数目  
	cout << "num:";
	cin >> n;
	cout << "data";
	for (int i = 0; i < n; i++)
	{
		int a;
		cin >> a;
		v.push_back(a);
	}
}

void sort_bin(vector<int> &v)
{
	while (1)
	{
		bool flag;//排序标记  
		int pStart = 1;//默认开始遍历的下标为2  
		if (v[1] == v[0])
		{
			while (v[pStart] == v[pStart - 1] && pStart < v.size())pStart++;//若元素相同，则判断下一个  
		}
		flag = v[pStart]>v[pStart - 1];//确定当前排序类型（升序、降序）  
		bool next = flag;
		for (int i = pStart + 1; i < v.size(); i++)
		{
			while (v[i] == v[i - 1] && i < v.size())i++;
			next = v[i]>v[i - 1];//确定当前元素与上一个比较后是升序还是降序  
			if (next == flag)//与原本序列违背  
				continue;
			auto _Start = &v[0];
			int *_End;
			//while (v[i] == v[0] && i < v.size())i++;  
			if (flag == v[i] > v[0] && v[i] != v[0])
			{
				_End = &v[i];
			}
			else
			{
				_End = &v[i - 1];
			}
			reverse(_Start, _End + 1);
			for_each(v.begin(), v.end(), printData); cout << endl;
			T++;
			break;
		}//for  
		if (next == flag&&flag)break;
		else if (next == flag&&flag == false)
		{
			reverse(v.begin(), v.end());
			for_each(v.begin(), v.end(), printData); cout << endl;
			T++;
		}
	}//while  
}

int main(void)
{
	vector<int> v;
	init_bin(v);

	sort_bin(v);
	cout << endl;
	cout << "times: " << T << endl;
	system("pause");
	return 0;
}
