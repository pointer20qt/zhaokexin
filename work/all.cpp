#include "a.h"
#include<iostream>
using namespace std;
#include "c.h"
#pragma comment(lib,"Win32Project1.lib") 
#include<vector>
using namespace std;
#include<string>
//异常
/*int main()
{
	vector<int> arr{ 1, 2, 3, 4, 5 };
	//throw功能：抛出异常,并发送一个任意类型的对象

	try
	{
		for (int i = 0; i < 6; i++)
		{
			cout << arr.at(i) << endl;
		}
		cout << "打印完了" << endl;
		throw 6;
	}
	catch (int s)
	{
		cout << "发生了异常，异常对象" << s << endl;
	}
	catch (out_of_range& e)
	{

		cout << "数组越界异常" << endl;
	}
	catch (...)//捕获所有异常
	{
		cout << "异常" << endl;
	}
	cout << "finally" << endl;
}
*/

//类：成员的集合，成员：成员方法、成员变量
//struct默认所有成员都是公有的
//class默认所有成员都是私有的
/*class school
{
	string schoolName;
	string schoolType;
	string address;	
	//初始化需要一个函数，声明了一个方法：构造方法
public:
	school(string schoolName, string schoolType, string address)
	{
		//this
		this->schoolName = schoolName;
		this->schoolType = schoolType;
		this->address = address;
	}

};

void initSchool(school* _this,string schoolName, string schoolType, string address)
{
	_this->schoolName = schoolName;
	_this->schoolType = schoolType;
	_this->address = address;
}//面向对象：封装

int main()
{
	school* s1 = (school*)malloc(sizeof(school));
	initSchool(s1,"指针", "就业", "大庆");
	
	school* s2 = new school("指针", "就业", "大庆");
}*/


//深拷贝、浅拷贝
class principal{
std::string name;
	//...
public:
	principal(std::string sname){
		this->name = sname;
	}
	~principal(){
		cout << "杨老师下班了" << endl;
	}
};
class school{
public:
	//学校名
	std::string schoolName;
	//学校类别，小学，高中，大学
	std::string schoolType;
	//学校地址
	std::string address;
	principal* master;
	//默认的构造函数将所有成员对象 调用其默认构造方法
	//school() = default;
	//school(){}

	~school(){
		delete master;
	}
	//this是自动传进去一个参数，因为 所有成员方法都需要传一个this指针
	school(std::string schoolName, std::string schoolType, std::string address){
		this->schoolName = schoolName;
		this->address = address;
		this->schoolType = schoolType;
		master = new principal("杨老师");
	}
	//拷贝出一个一样的
	school(const school& p){
		cout << "拷贝构造函数" << endl;
		master = new principal(*(p.master));
	}
	//递归调用所有成员对象的拷贝构造方法，如果不是对象，就复制
	//school(const school& p) :schoolName(p.schoolName), schoolType(p.schoolType),address(p.address),
	//d(p.d){

	//}
};



void school_init(school* _this, std::string schoolName, std::string schoolType, std::string address){
	_this->schoolName = schoolName;
	_this->address = address;
	_this->schoolType = schoolType;
}
void school_schoolOpens(school* _this){
	cout << _this->schoolName << "开学了" << endl;
}
void swap(school A, school B){
	school tem=A;
	//赋值拷贝  构造拷贝
	//以浅拷贝的方式让B跟A一样
	//B = A;
	//A = tem;
}

//函数会创造出新的变量，内容和传入的参数一样
void swap(int a, int b){
	int tem = a;
	a = b;
	b = tem;
}
void run(){
	school s1("东北石油大学", "大学", "大庆");
	school s2("八一农垦大学", "大学", "大庆");
	swap(s1, s2);
}
int main(){
	run();
	cout << "下一句代码" << endl;

}