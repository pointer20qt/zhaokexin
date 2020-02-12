#include<iostream>
#include<vector>
#include<string>

using namespace std;


//C
typedef struct node
{

}st;
//C++
//重定义类型
typedef int I;//原类型：int  新类型：I
using I = int;
//函数返回类型是void，接受参数是int, const std::string&，两种不同语法的写法不同。
typedef void(*FP) (int, const std::string&);  //函数指针
using FP = void(*) (int, const std::string&);


//友元
/*class A
{
public:
	void run(school s)
	{
		s.schoolName;
	}
};
class school{
	friend class A;
	std::string schoolName;
	std::string schoolType;
	std::string address;
public:
}*/

/*void start(school s)
{
	s.schoolName;
}
class school{
	friend void start(school s);
	std::string schoolName;
	std::string schoolType;
	std::string address;
public:
*/

/*class A
{
public:
	void run(school s)
	{

	}
};
class school{
	friend void A::run(school s);
	std::string schoolName;
	std::string schoolType;
	std::string address;
public:
}*/



class principal{
	std::string name;
	//...
public:
	principal(std::string sname){
		this->name = sname;
	}
	~principal(){
		cout << name<<"下班了" << endl;
	}
};


class school{
public:
	std::string schoolName;
	std::string schoolType;
	std::string address;

	principal* master;
	~school(){
		cout << schoolName << "放假了" << endl;
		delete master;
	}
	school(std::string schoolName, std::string schoolType, std::string address){
		cout << "普通构造函数" << endl;
		this->schoolName = schoolName;
		this->address = address;
		this->schoolType = schoolType;
		master = new principal("杨老师");
	}
	school(const school& p):schoolName(p.schoolName),schoolType(p.schoolType),address(p.address){//初始化参数列表

		cout << this->schoolName<<"拷贝建立了" << endl;
		master = new principal(*(p.master));//new一块新的空间，并用新的对象拷贝构造
	}
	//类有默认的移动构造
	school(school&& other) :schoolName(other.schoolName), schoolType(other.schoolType), address(other.address)
	{
		cout << "移动构造" << endl;
		master = other.master;
		other.master = NULL;
	}
};

school getschool()
{
	school s2("东北石油大学", "大学", "大庆");//1)普通构造
	return s2;//school(s2)
}
int main(){
	school s2("东北石油大学", "大学", "大庆");
	school s1(std::move(s2));
	cout << "下一句代码" << endl;
}
