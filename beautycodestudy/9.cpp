/*
��һ�������մ�С����ںá�����С����С���ϣ�������
ֻ����һֻ�֣�һ��ץס������ļ���������������µߵ���������
��������֮���ź���
������n���С��һ���ӱ������ٷ�ת���Σ����ܴﵽ��С����Ľ����
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
	int n;//��Ҫ����ı�����Ŀ  
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
		bool flag;//������  
		int pStart = 1;//Ĭ�Ͽ�ʼ�������±�Ϊ2  
		if (v[1] == v[0])
		{
			while (v[pStart] == v[pStart - 1] && pStart < v.size())pStart++;//��Ԫ����ͬ�����ж���һ��  
		}
		flag = v[pStart]>v[pStart - 1];//ȷ����ǰ�������ͣ����򡢽���  
		bool next = flag;
		for (int i = pStart + 1; i < v.size(); i++)
		{
			while (v[i] == v[i - 1] && i < v.size())i++;
			next = v[i]>v[i - 1];//ȷ����ǰԪ������һ���ȽϺ��������ǽ���  
			if (next == flag)//��ԭ������Υ��  
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
