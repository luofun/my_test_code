//#include<stdio.h>
//#include<string.h>
#include<string>
#include<iostream>

const double Threadhold = 1E-6;
const int CardsNumber = 4;
const int ResultValue = 24;
double number[CardsNumber];
std::string result[CardsNumber];

bool PointGame(int n)
{
	if (n == 1)
	{
		if (fabs(number[0] - ResultValue) < Threadhold)
		{
			std::cout << result[0] << std::endl;
			return true;
		}
		else
		{
			return false;
		}
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			double a, b;
			std::string expa, expb;
			a = number[i];
			b = number[j];
			number[j] = number[n - 1];
			expa = result[i];
			expb = result[j];
			result[j] = result[n - 1];

			result[i] = '(' + expa + '+' + expb + ')';
			number[i] = a + b;
			if (PointGame(n - 1))
				return true;

			result[i] = '(' + expa + '-' + expb + ')';
			number[i] = a - b;
			if (PointGame(n - 1))
				return true;

			result[i] = '(' + expb + '-' + expa + ')';
			number[i] = b - a;
			if (PointGame(n - 1))
				return true;

			result[i] = '(' + expa + '*' + expb + ')';
			number[i] = a * b;
			if (PointGame(n - 1))
				return true;
			if (b != 0)
			{
				result[i] = '(' + expa + '/' + expb + ')';
				number[i] = a / b;
				if (PointGame(n - 1))
					return true;
			}

			if (a != 0)
			{
				result[i] = '(' + expb + '/' + expa + ')';
				number[i] = b / a;
				if (PointGame(n - 1))
					return true;
			}
			number[i] = a;
			number[j] = b;
			result[i] = expa;
			result[j] = expb;

		}
	}
	return false;


}

void main(){
	int x;
	for (int i = 0; i < CardsNumber; i++)
	{
		char buffer[20];
		std::cout << "the" << i << "th number:";
		std::cin >> x;
		number[i] = x;
		itoa(x, buffer, 10);
		result[i] = buffer;
	}
	if (PointGame(CardsNumber))
	{
		std::cout << "Success" << std::endl;

	}
	else
	{
		std::cout << "Fail." << std::endl;
	}

}