#include<iostream>
#include<string>
#include"auto_new.h"
using namespace std;
class tool{
public:
	int value;
	tool(){
		cout << "tool����" << endl;
	}
	tool(int a){
		cout << "tool���ι���" << endl;
	}
	tool(const tool&){
		cout << "tool��������" << endl;
	}
	tool(tool&&){
		cout << "tool�ƶ�����" << endl;
	}
	~tool(){
		cout << "tool����" << endl;
	}
	tool& operator = (const tool&){
		cout << "tool������ֵ" << endl;
		return *this;//���ص�ǰ����
	}
	tool& operator = (tool&&){
		cout << "tool�ƶ���ֵ" << endl;
		return *this;
	}
};

int main()
{
	tool* p = new tool;
	auto_ptr<tool>ptr(p);
	ptr.reset(p);

	x_auto_ptr<tool>ptr1{ new tool };
	x_auto_ptr<tool>ptr2(ptr1);
	x_auto_ptr<tool>ptr3;
	ptr3 = ptr2;
	(*ptr3).value;
	ptr2->value;
	return 0;
}