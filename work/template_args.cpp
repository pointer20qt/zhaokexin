/*
��ҵ3��ģ��������ĵݹ���
*/
#include<iostream>
#include<vector>
using namespace std;

template<class T, class... args> void xprint(T f, args... d){
	cout << f << endl;
	xprint(d...);
}
//�ݹ鵽�޲ε�ʱ���Ӧ�ý�����
void xprint(){
	cout << "�ݹ���stop" << endl;
}
template<class T, class T2, class T3, class... args> void xprint3(T f, T2 f2, T3 f3, args... d){
	cout << "��һ��" << f << "�ڶ���" << f2 << "������" << f3 << endl;
	xprint3(d...);
}
void xprint3(){
	cout << "�ݹ���stop" << endl;
}

int main()
{
	xprint(1, 10, 99, 10, 5, 91);
	cout << "00000000000" << endl;
	xprint3(1, 10, 99 ,10, 5,91);
	return 0;
}
