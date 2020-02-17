#pragma once
template<class T>
class x_auto_ptr{
	T* obj = nullptr;
public:
	x_auto_ptr(T* ptr) :obj(ptr){
		//obj = ptr;
	}
	x_auto_ptr() = default;//无参构造方法
	~x_auto_ptr(){
		delete obj;
	}
	//模板类附上模板类型才可以
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