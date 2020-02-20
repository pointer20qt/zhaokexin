#include<iostream>
#include<time.h>
using namespace std;


bool r(double n)
{
	//0-1的随机小数
	double p = ((double)rand()) / RAND_MAX;
	if (p > n)
	{
		return true;
	}
	else
	{
		return false;
	}
}
int main()
{
	//初始化随机种子
	//time(0)获得从1970年到现在的秒数
	srand(time(0));
	//获得一个随机数
	//rand();
	//[0,a)
	//rand() % a;
	//[a,b)
	//rand() % (b - a) + a;
	
	int s = 0, t = 0;
	for (int i = 0; i < 100; i++)
	{
		if (r(0.5))
		{
			s++;
		}
		else
		{
			t++;
		}
	}
	
	//a-b的随机小数
	//3-5
	double tmp = ((double)rand()) / RAND_MAX * 2 + 3;
	cout << tmp << endl;
}

