#include<iostream>
#include<string>
#include<initializer_list>
#define NDEBUG
#include<assert.h>
#include<vector>
using namespace std;

static_assert (sizeof(int) != 32, "Inappropriate int size");

class vec{
	int * num;
	int n;
public:
	//initializer_list<int>��vector<int>�������ͣ�int����
	vec(initializer_list<int> arr) //�ں�������ʱarr�ͻ���ʧ
	{
		n = arr.size();
		num = new int[arr.size()];
		//num�����µ�arr��С�Ŀռ�
		for (int i = 0; i < arr.size(); i++)//����ѭ����arr������д��obj
		{
			num[i] = *(arr.begin() + i);
		}
	}
	/*�����main�����vec v[2]��ֵ �أ���Ҫ��������
	ΪʲôҪ����&�أ�Ϊ�˱�֤v[]�ǿ��޸ĵ�*/
	int& operator[](int index){
		return num[index];
	}
};
class ve{
	vector<int> a;
public:
	ve(initializer_list<int> list) :a(list)	{

	}
	int& operator[](int number){
		assert(number >= 0 && number < a.size());//assert��һ������������������Ϊ0���ͻ����
		return a[number];
	}

};
int main(){
	vec v{ 1, 2, 3, 4 };
	cout << v[2] << endl;
	v[2] = 99;
	cout << v[2] << endl;
	ve arr{ 10, 5, 1, 10 };
	cout << arr[-2] << endl;//��ָ��������λ��
	return 0;
}