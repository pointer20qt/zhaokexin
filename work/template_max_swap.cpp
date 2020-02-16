#include<iostream>
#include<string>
#include<initializer_list>
using namespace std;

int Lmax(int a, int b){
	cout << "int函数比较" << endl;
	return a > b ? a : b;
}

double Lmax(double a, double b){
	cout << "double函数比较" << endl;
	return a > b ? a : b;
}
//template关键字 class、typname类型 T名字
template<class T> T Lmax(T a, T b){
	cout << "模板函数比较" << endl;
	return a > b ? a : b;
}
template<class T1, class T2> T1 Lmax(T1 a, T2 b){
	cout << "模板函数比较" << endl;
	return a > b ? a : b;
}
template<int d, class T1, class T2> T1 Lmax(T1 a, T2 b){
	int arr(d);
	cout << arr << endl;
	cout << "模板函数比较" << endl;
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
	cout << "cout输出了Z类型的变量" << endl;
	return o;
}
//代码膨胀，模板写代码，根据调用参数的不同，会按照模板推导出完整的代码

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
	char* p;//会出现浅拷贝问题
	x(int v){
		p = new char[10];
		value = v;
	}
	//使用委托函数
	x(const x& other) :x(other.value){
		p = new char[10];
		std::cout << "拷贝" << endl;
	}
	//重载类型，将原本的类型换成int
	operator int(){
		cout << "转化为int" << endl;
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
	//tem、a、b都有自己的p
	x t = a;
	//a里是b的p
	a.operator  = (b);//operator（复制赋值）在创建的时候调用的浅拷贝，在释放空间的时候就会出现错误
	//b里是t的p
	b.operator = (t);//处理方法就是重载函数
}

int main(){
	int x1 = 10, x2 = 01;
	double d1 = 10.05, d2 = 1.1;
	cout << Lmax(x1, x2) << endl;//Lmax可以根据传进的参数来推导类型
	cout << Lmax(d1, d2) << endl;//隐式推导，若类型不一样会推导不了
	cout << Lmax<double>(x1, d2) << endl;//显式推导，相当于指定模板，必须使用模板函数
	cout << Lmax<>(x1, x2) << endl;//显式指定模板,当有int类型的时候也会调用模板
	Z a, b;
	cout << Lmax(a, b) << endl;//让cout识别并输出Z需要进行在类中和全局的重载操作
	cout << Lmax(x1, d2) << endl;//多个参数的模板
	cout << Lmax<10>(x1, d2) << endl;

	Tswap(x1, x2);
	cout << x1 << "int类型" << x2 << endl;
	x z1(10), z2(5);
	int n = z1.operator int();
	//z1.value = 01;
	//z2.value = 10;
	Tswap(z1, z2);//通过拷贝构造进行与模板进行匹配
	cout << z1.value << "自定义类型" << z2.value << endl;
	cout << z1 << "自定义类型" << z2 << endl;//因为有operator int()，可以将z1转化成int

	x z3(11), z4(23);
	Tswap(z3, z4);
	cout << z3 << "自定义类型" << z4 << endl;
	return 0;
}
