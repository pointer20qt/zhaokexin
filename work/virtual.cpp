#include <iostream>
using namespace std;
#include<string>


//��������
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
		cout << "���ظ���" << endl;
	}
};
int main()
{
	university u;
	u.schoolopens();	
}
*/

//�麯������������
//����ָ�롢�������
/*class school{
	std::string schoolName;
	std::string schoolType;
	std::string address;
public:
	~school(){
		cout << schoolName << "�ż���" << endl;
	}
	school(std::string schoolName, std::string schoolType, std::string address){
		cout << "��ͨ���캯��" << endl;
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
		cout << this->schoolName << "��ѧ" << endl;
	}
};

class university :public school
{
public:
	university() :school("����ʯ�ʹ�ѧ", "��ѧ", "����")
	{

	}
	virtual void schoolopens()
	{
		cout << getschoolname() << "��ѧ����" << endl;
	}
};
//����ָ�롢�������
//�������Ƿ����麯��������Ǿ͵�����д���
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
		cout << name << "�°���" << endl;
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
	school(const school& p) :schoolName(p.schoolName), schoolType(p.schoolType), address(p.address){//��ʼ�������б�
		schoolName = p.schoolName;
		cout << this->schoolName << "����������" << endl;
		master = new principal(*(p.master));//newһ���µĿռ䣬�����µĶ��󿽱�����
	}
	//����Ĭ�ϵ��ƶ�����
	school(school&& other) :schoolName(other.schoolName), schoolType(other.schoolType), address(other.address)
	{
		cout << "�ƶ�����" << endl;
		master = other.master;
		other.master = NULL;
	}
	virtual void schoolopens()
	{
		cout << this->schoolName << "��ѧ" << endl;
	}
};

class university :public school
{
public:
	principal* p;
	university() :school("����ʯ�ʹ�ѧ", "��ѧ", "����")
	{
		cout << "��ѧ�Ĺ��캯��" << endl;
		p = new principal("c++");
	}
	void schoolopens()
	{
		cout << getschoolname() << "��ѧ����" << endl;
	}
	~university(){
		cout << "��ѧ��xigou����" << endl;
		delete p;
	}
};
void printschool(school* school)
{
	school->schoolopens();
	delete school;
}

int main(){
	school *s=new school("�����׶�԰", "�׶�԰", "����");
	university *u=new university();
	printschool(u);

}

