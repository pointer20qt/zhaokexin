/*
作业3：模板参数包的递归拆包
*/
#include<iostream>
#include<vector>
using namespace std;

template<class T, class... args> void xprint(T f, args... d){
	cout << f << endl;
	xprint(d...);
}
//递归到无参的时候就应该结束了
void xprint(){
	cout << "递归拆包stop" << endl;
}
template<class T, class T2, class T3, class... args> void xprint3(T f, T2 f2, T3 f3, args... d){
	cout << "第一个" << f << "第二个" << f2 << "第三个" << f3 << endl;
	xprint3(d...);
}
void xprint3(){
	cout << "递归拆包stop" << endl;
}

int main()
{
	xprint(1, 10, 99, 10, 5, 91);
	cout << "00000000000" << endl;
	xprint3(1, 10, 99 ,10, 5,91);
	return 0;
}
