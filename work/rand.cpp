#include<iostream>
#include<time.h>
using namespace std;


bool r(double n)
{
	//0-1�����С��
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
	//��ʼ���������
	//time(0)��ô�1970�굽���ڵ�����
	srand(time(0));
	//���һ�������
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
	
	//a-b�����С��
	//3-5
	double tmp = ((double)rand()) / RAND_MAX * 2 + 3;
	cout << tmp << endl;
}

