#pragma once
template<class T>
class x_auto_ptr{
	T* obj = nullptr;
public:
	x_auto_ptr(T* ptr) :obj(ptr){
		//obj = ptr;
	}
	x_auto_ptr() = default;//�޲ι��췽��
	~x_auto_ptr(){
		delete obj;
	}
	//ģ���฽��ģ�����Ͳſ���
	x_auto_ptr(x_auto_ptr<T>& ptr) :obj(ptr.release()){
		//obj = ptr.obj;
		//ptr.obj = nullptr;
	}
	x_auto_ptr& operator = (x_auto_ptr<T>& ptr){
		/*delete obj;
		obj = ptr.obj;
		ptr.obj = nullptr;*/
		obj = ptr.release();
		return *this;
	}
	void reset(T*newptr = nullptr){
		delete obj;
		obj = newptr;
	}
	T* release(){
		auto temp = obj;
		obj = nullptr;
		return temp;
	}
	T& operator*(){
		return *obj;
	}
	T* operator->(){
		return obj;
	}
	T* get(){
		return obj;
	}
};