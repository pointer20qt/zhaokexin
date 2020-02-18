#include<iostream>
#include<initializer_list>
#include<string>
#include<vector>
using namespace std;

//栈，先入后出，push\pop\top\size\empty
template <class T> class L_stack
{
	std::vector<T> arr;
public:
	void push(T&& obj)
	{
		arr.push_back(obj);
	}
	void pop()
	{
		arr.pop_back();
	}
	T& top()
	{
		return arr.back();
	}
	size_t size()//size_t===typedef unsigned int
	{
		return arr.size();
	}
	bool empty()
	{
		return arr.empty();
	}
};
int main()
{
	L_stack<int> l;
	l.push(5);
	l.push(6);
	l.push(7);
	cout << l.top() << endl;
	l.pop();
	cout << l.top() << endl;
	cout << l.size() << endl;

	cout << "运行结束" << endl;
}



