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
	//initializer_list<int>与vector<int>样的类型，int数组
	vec(initializer_list<int> arr) //在函数结束时arr就会消失
	{
		n = arr.size();
		num = new int[arr.size()];
		//num申请新的arr大小的空间
		for (int i = 0; i < arr.size(); i++)//经过循环将arr的数组写入obj
		{
			num[i] = *(arr.begin() + i);
		}
	}
	/*如何再main中输出vec v[2]的值 呢，需要进行重载
	为什么要返回&呢，为了保证v[]是可修改的*/
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
		assert(number >= 0 && number < a.size());//assert是一个布尔类型若（）内为0；就会出错
		return a[number];
	}

};
int main(){
	vec v{ 1, 2, 3, 4 };
	cout << v[2] << endl;
	v[2] = 99;
	cout << v[2] << endl;
	ve arr{ 10, 5, 1, 10 };
	cout << arr[-2] << endl;//会指出程序错的位置
	return 0;
}