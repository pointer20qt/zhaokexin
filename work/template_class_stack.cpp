/*
��ҵ2����ģ���װvectorʵ��stack
*/
#include<iostream>
#include<vector>
using namespace std;
//ģ��ջ
template<class T> class x_stack{
	vector<T>num;
public:
	//push��Ҫ������&
	void push(T&& obj){
		num.push_back(obj);
	}
	void pop(){
		num.pop_back();
	}
	T& top(){
		return num.back();//���һ��Ԫ��
	}
	size_t size(){
		return num.size();
	}
	bool empty(){
		return num.empty();
	}
};
int main()
{
	x_stack<int> x;
	x.push(1);
	x.push(10);
	x.push(5);
	cout << x.top() << endl;
	x.pop();
	cout << x.top() << endl;
	cout << x.size() << endl;//ջ���滹�м���
	return 0;
}