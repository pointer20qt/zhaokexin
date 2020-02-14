#include <iostream>
using namespace std;
#include<string>


//函数隐藏
/*
class school{
	std::string schoolName;
	std::string schoolType;
	std::string address;
public:
	
	void schoolopens()
	{
		cout << this->schoolName << endl;
	}
	void schoolopens(int i)
	{
		for (int tem = 0; tem < i; tem++)
		{
			cout << this->schoolName << endl;
		}		
	}
};
class university :public school
{
public:
	
	void schoolopens()
	{
		cout << "隐藏父类" << endl;
	}
};
int main()
{
	university u;
	u.schoolopens();	
}
*/

//虚函数、函数覆盖
//父类指针、子类对象
/*class school{
	std::string schoolName;
	std::string schoolType;
	std::string address;
public:
	~school(){
		cout << schoolName << "放假了" << endl;
	}
	school(std::string schoolName, std::string schoolType, std::string address){
		cout << "普通构造函数" << endl;
		this->schoolName = schoolName;
		this->address = address;
		this->schoolType = schoolType;
	}
	std::string getschoolname()
	{
		return schoolName;
	}
	virtual void schoolopens()
	{
		cout << this->schoolName << "开学" << endl;
	}
};

class university :public school
{
public:
	university() :school("东北石油大学", "大学", "大庆")
	{

	}
	virtual void schoolopens()
	{
		cout << getschoolname() << "开学典礼" << endl;
	}
};
//父类指针、子类对象
//看父类是否是虚函数，如果是就调用重写后的
//void printschool(school* school)
//{
//	school->schoolopens();
//}
void printschool(school& school)
{
	school.schoolopens();
}

int main(){
	university u;
	printschool(u);
}
*/

class principal{
	std::string name;
	//...
public:
	principal(std::string sname){
		this->name = sname;
	}
	~principal(){
		cout << name << "下班了" << endl;
	}
};
class school{
	std::string schoolName;
	std::string schoolType;
	std::string address;
public:
	std::string getschoolname()
	{
		return schoolName;
	}
	principal* master;
	virtual ~school(){
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
	school(const school& p) :schoolName(p.schoolName), schoolType(p.schoolType), address(p.address){//初始化参数列表
		schoolName = p.schoolName;
		cout << this->schoolName << "拷贝建立了" << endl;
		master = new principal(*(p.master));//new一块新的空间，并用新的对象拷贝构造
	}
	//类有默认的移动构造
	school(school&& other) :schoolName(other.schoolName), schoolType(other.schoolType), address(other.address)
	{
		cout << "移动构造" << endl;
		master = other.master;
		other.master = NULL;
	}
	virtual void schoolopens()
	{
		cout << this->schoolName << "开学" << endl;
	}
};

class university :public school
{
public:
	principal* p;
	university() :school("东北石油大学", "大学", "大庆")
	{
		cout << "大学的构造函数" << endl;
		p = new principal("c++");
	}
	void schoolopens()
	{
		cout << getschoolname() << "开学典礼" << endl;
	}
	~university(){
		cout << "大学的xigou函数" << endl;
		delete p;
	}
};
void printschool(school* school)
{
	school->schoolopens();
	delete school;
}

int main(){
	school *s=new school("春天幼儿园", "幼儿园", "春天");
	university *u=new university();
	printschool(u);

}

