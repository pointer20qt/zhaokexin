#include "a.h"
#include<iostream>
using namespace std;
#include "c.h"
#pragma comment(lib,"Win32Project1.lib") 
#include<vector>
using namespace std;
#include<string>
//�쳣
/*int main()
{
	vector<int> arr{ 1, 2, 3, 4, 5 };
	//throw���ܣ��׳��쳣,������һ���������͵Ķ���

	try
	{
		for (int i = 0; i < 6; i++)
		{
			cout << arr.at(i) << endl;
		}
		cout << "��ӡ����" << endl;
		throw 6;
	}
	catch (int s)
	{
		cout << "�������쳣���쳣����" << s << endl;
	}
	catch (out_of_range& e)
	{

		cout << "����Խ���쳣" << endl;
	}
	catch (...)//���������쳣
	{
		cout << "�쳣" << endl;
	}
	cout << "finally" << endl;
}
*/

//�ࣺ��Ա�ļ��ϣ���Ա����Ա��������Ա����
//structĬ�����г�Ա���ǹ��е�
//classĬ�����г�Ա����˽�е�
/*class school
{
	string schoolName;
	string schoolType;
	string address;	
	//��ʼ����Ҫһ��������������һ�����������췽��
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
}//������󣺷�װ

int main()
{
	school* s1 = (school*)malloc(sizeof(school));
	initSchool(s1,"ָ��", "��ҵ", "����");
	
	school* s2 = new school("ָ��", "��ҵ", "����");
}*/


//�����ǳ����
class principal{
std::string name;
	//...
public:
	principal(std::string sname){
		this->name = sname;
	}
	~principal(){
		cout << "����ʦ�°���" << endl;
	}
};
class school{
public:
	//ѧУ��
	std::string schoolName;
	//ѧУ���Сѧ�����У���ѧ
	std::string schoolType;
	//ѧУ��ַ
	std::string address;
	principal* master;
	//Ĭ�ϵĹ��캯�������г�Ա���� ������Ĭ�Ϲ��췽��
	//school() = default;
	//school(){}

	~school(){
		delete master;
	}
	//this���Զ�����ȥһ����������Ϊ ���г�Ա��������Ҫ��һ��thisָ��
	school(std::string schoolName, std::string schoolType, std::string address){
		this->schoolName = schoolName;
		this->address = address;
		this->schoolType = schoolType;
		master = new principal("����ʦ");
	}
	//������һ��һ����
	school(const school& p){
		cout << "�������캯��" << endl;
		master = new principal(*(p.master));
	}
	//�ݹ�������г�Ա����Ŀ������췽����������Ƕ��󣬾͸���
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
	cout << _this->schoolName << "��ѧ��" << endl;
}
void swap(school A, school B){
	school tem=A;
	//��ֵ����  ���쿽��
	//��ǳ�����ķ�ʽ��B��Aһ��
	//B = A;
	//A = tem;
}

//�����ᴴ����µı��������ݺʹ���Ĳ���һ��
void swap(int a, int b){
	int tem = a;
	a = b;
	b = tem;
}
void run(){
	school s1("����ʯ�ʹ�ѧ", "��ѧ", "����");
	school s2("��һũ�Ѵ�ѧ", "��ѧ", "����");
	swap(s1, s2);
}
int main(){
	run();
	cout << "��һ�����" << endl;

}