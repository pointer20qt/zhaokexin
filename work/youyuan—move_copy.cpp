#include<iostream>
#include<vector>
#include<string>

using namespace std;


//C
typedef struct node
{

}st;
//C++
//�ض�������
typedef int I;//ԭ���ͣ�int  �����ͣ�I
using I = int;
//��������������void�����ܲ�����int, const std::string&�����ֲ�ͬ�﷨��д����ͬ��
typedef void(*FP) (int, const std::string&);  //����ָ��
using FP = void(*) (int, const std::string&);


//��Ԫ
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
		cout << name<<"�°���" << endl;
	}
};


class school{
public:
	std::string schoolName;
	std::string schoolType;
	std::string address;

	principal* master;
	~school(){
		cout << schoolName << "�ż���" << endl;
		delete master;
	}
	school(std::string schoolName, std::string schoolType, std::string address){
		cout << "��ͨ���캯��" << endl;
		this->schoolName = schoolName;
		this->address = address;
		this->schoolType = schoolType;
		master = new principal("����ʦ");
	}
	school(const school& p):schoolName(p.schoolName),schoolType(p.schoolType),address(p.address){//��ʼ�������б�

		cout << this->schoolName<<"����������" << endl;
		master = new principal(*(p.master));//newһ���µĿռ䣬�����µĶ��󿽱�����
	}
	//����Ĭ�ϵ��ƶ�����
	school(school&& other) :schoolName(other.schoolName), schoolType(other.schoolType), address(other.address)
	{
		cout << "�ƶ�����" << endl;
		master = other.master;
		other.master = NULL;
	}
};

school getschool()
{
	school s2("����ʯ�ʹ�ѧ", "��ѧ", "����");//1)��ͨ����
	return s2;//school(s2)
}
int main(){
	school s2("����ʯ�ʹ�ѧ", "��ѧ", "����");
	school s1(std::move(s2));
	cout << "��һ�����" << endl;
}
