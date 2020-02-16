/*
作业2：类模板封装vector实现stack
*/
#include<iostream>
#include<vector>
using namespace std;
//模拟栈
template<class T> class x_stack{
	vector<T>num;
public:
	//push中要有两个&
	void push(T&& obj){
		num.push_back(obj);
	}
	void pop(){
		num.pop_back();
	}
	T& top(){
		return num.back();//最后一个元素
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
	cout << x.size() << endl;//栈里面还有几个
	return 0;
}