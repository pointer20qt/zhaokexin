#include<iostream>
#include<string>
#include<initializer_list>
using namespace std;

int Lmax(int a, int b){
	cout << "int�����Ƚ�" << endl;
	return a > b ? a : b;
}

double Lmax(double a, double b){
	cout << "double�����Ƚ�" << endl;
	return a > b ? a : b;
}
//template�ؼ��� class��typname���� T����
template<class T> T Lmax(T a, T b){
	cout << "ģ�庯���Ƚ�" << endl;
	return a > b ? a : b;
}
template<class T1, class T2> T1 Lmax(T1 a, T2 b){
	cout << "ģ�庯���Ƚ�" << endl;
	return a > b ? a : b;
}
template<int d, class T1, class T2> T1 Lmax(T1 a, T2 b){
	int arr(d);
	cout << arr << endl;
	cout << "ģ�庯���Ƚ�" << endl;
	return a > b ? a : b;
}

class Z{
public:
	bool operator>(Z&)
	{
		return true;
	}
};
ostream& operator<<(ostream& o, Z& z){
	cout << "cout�����Z���͵ı���" << endl;
	return o;
}
//�������ͣ�ģ��д���룬���ݵ��ò����Ĳ�ͬ���ᰴ��ģ���Ƶ��������Ĵ���

void Tswap(int& a, int& b){
	int t = a;
	a = b;
	b = t;
}

void Tswap(double& a, double& b){
	double t = a;
	a = b;
	b = t;
}

template<class T> void Tswap(T& a, T& b){
	T t = a;
	a = b;
	b = t;
}

class x{
public:
	int value = 0;
	char* p;//�����ǳ��������
	x(int v){
		p = new char[10];
		value = v;
	}
	//ʹ��ί�к���
	x(const x& other) :x(other.value){
		p = new char[10];
		std::cout << "����" << endl;
	}
	//�������ͣ���ԭ�������ͻ���int
	operator int(){
		cout << "ת��Ϊint" << endl;
		return value;
	}
	x& operator=(const x& other){
		delete p;
		p = new char[10];
		value = other.value;
		return *this;
	}
	~x(){
		delete p;
	}
};
void Tswap(x& a, x& b){
	//tem��a��b�����Լ���p
	x t = a;
	//a����b��p
	a.operator  = (b);//operator�����Ƹ�ֵ���ڴ�����ʱ����õ�ǳ���������ͷſռ��ʱ��ͻ���ִ���
	//b����t��p
	b.operator = (t);//�������������غ���
}

int main(){
	int x1 = 10, x2 = 01;
	double d1 = 10.05, d2 = 1.1;
	cout << Lmax(x1, x2) << endl;//Lmax���Ը��ݴ����Ĳ������Ƶ�����
	cout << Lmax(d1, d2) << endl;//��ʽ�Ƶ��������Ͳ�һ�����Ƶ�����
	cout << Lmax<double>(x1, d2) << endl;//��ʽ�Ƶ����൱��ָ��ģ�壬����ʹ��ģ�庯��
	cout << Lmax<>(x1, x2) << endl;//��ʽָ��ģ��,����int���͵�ʱ��Ҳ�����ģ��
	Z a, b;
	cout << Lmax(a, b) << endl;//��coutʶ�����Z��Ҫ���������к�ȫ�ֵ����ز���
	cout << Lmax(x1, d2) << endl;//���������ģ��
	cout << Lmax<10>(x1, d2) << endl;

	Tswap(x1, x2);
	cout << x1 << "int����" << x2 << endl;
	x z1(10), z2(5);
	int n = z1.operator int();
	//z1.value = 01;
	//z2.value = 10;
	Tswap(z1, z2);//ͨ���������������ģ�����ƥ��
	cout << z1.value << "�Զ�������" << z2.value << endl;
	cout << z1 << "�Զ�������" << z2 << endl;//��Ϊ��operator int()�����Խ�z1ת����int

	x z3(11), z4(23);
	Tswap(z3, z4);
	cout << z3 << "�Զ�������" << z4 << endl;
	return 0;
}
