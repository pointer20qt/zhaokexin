#pragma once
//模板化，可以接受任意类型参数
//构造方法，赋值一个指针
//析构方法，释放指针
//不标准的复制构造（转移内部指针控制权）
//不标准的复制赋值（转移内部指针控制权）
//reset  释放之前的，获取新的指针
//release  释放控制权，返回指针
//operator*()  模拟指针访问方法
//operator->()  模拟指针箭头方式访问方法
//get()  获得指针指向的指针
template<class T> class L_autoPtr
{
	T* obj = nullptr;
public:
	L_autoPtr(T* ptr) :obj(ptr)
	{
	}
	L_autoPtr() = default;
	~L_autoPtr()
	{
		delete obj;
	}

	L_autoPtr(L_autoPtr<T>& ptr) :obj(ptr.release())
	{

	}

	L_autoPtr& operator=(L_autoPtr<T>& ptr)
	{
		obj = ptr.release();
		return *this;
	}

	void reset(T* newPtr = nullptr)
	{
		delete obj;
		return newPtr;
	}
	T* release()
	{
		auto tmp = obj;
		obj = nullptr;
		return tmp;
	}
	T& operator*()
	{
		return *this;
	}
	T* operator->()
	{
		return obj;
	}
	T* get()
	{
		return obj;
	}
};

template<class T> class L_uniquePtr
{
	T* obj = nullptr;
public:
	L_uniquePtr(T* ptr) :obj(ptr)
	{
	}
	L_uniquePtr(const T&) = delete;
	L_uniquePtr() = default;
	~L_uniquePtr()
	{
		delete obj;
	}

	L_uniquePtr(const L_uniquePtr<T>&) = delete;
	L_uniquePtr(L_uniquePtr<T>&& ptr) :obj(ptr.release())
	{

	}

	L_uniquePtr& operator=(L_uniquePtr<T>&& ptr)
	{
		obj = ptr.release();
		return *this;
	}

	void reset(T* newPtr = nullptr)
	{
		delete obj;
		return newPtr;
	}
	T* release()
	{
		auto tmp = obj;
		obj = nullptr;
		return tmp;
	}
	T& operator*()
	{
		return *this;
	}
	T* operator->()
	{
		return obj;
	}
	T* get()
	{
		return obj;
	}
};

//命名空间：为了解决函数名和库函数名相同的问题
namespace zzz
{
	//资源计数类
	template<class T>
	class Ref{
		//当前资源计数
		int r_count = 0;
		//当前弱引用指针计数
		int w_count = 0;
		T* object = nullptr;
	public:
		Ref(T* target) :object(target){
			++r_count;
		}
		inline void increase(){
			r_count++;
		}
		inline void increase_w(){
			w_count++;
		}
		inline void reduce(){
			r_count--;
			if (r_count == 0){
				delete object;
				object = nullptr;
				//为什么112行要判断w_count是否为0 呢
				if (w_count == 0){
					delete this;
				}
			}
		}
		inline void reduce_w(){
			w_count--;
			//为什么要判断条件要加上r_count==0
			if (w_count == 0 && r_count == 0){
				delete this;
			}
		}
		//获得对对象
		T* get(){
			return object;
		}
		int getCount(){
			return r_count;
		}
	};
	//shared智能指针需要的方法
	/*
	无参构造，析构，传递指针构造，拷贝构造，移动构造，拷贝赋值，移动赋值,交换
	reset(T*)替换对象。 reset() 销毁对象
	operator*() operator->()
	get()获得裸指针
	use_count() 获得引用计数
	unique() 判断当前是否唯一  use_count()==1
	operator bool() 是否关联对象
	*/
	template<class T> class LweakPtr;
	template<class T> class LSharedPtr{
		friend class LweakPtr<T>;
		Ref<T>* ref = nullptr;
	public:
		LSharedPtr() = default;
		~LSharedPtr(){
			if (ref){
				ref->reduce();
			}
		}
		LSharedPtr(Ref<T>* newRef){
			ref = newRef;
			if (ref){
				ref->increase();
			}
		}
		LSharedPtr(T* newP){
			ref = new Ref<T>(newP);
		}
		LSharedPtr(const LSharedPtr& other){
			ref = other.ref;
			if (ref){
				ref->increase();
			}
		}
		LSharedPtr(LSharedPtr&& other){
			swap(ref, other.ref);
		}
		LSharedPtr& operator=(const LSharedPtr& other){
			if (ref){
				ref->reduce();
			}
			ref = other.ref;
			if (ref){
				ref->increase();
			}
			return *this;
		}
		LSharedPtr& operator=(LSharedPtr&& other){
			if (ref){
				ref->reduce();
			}
			ref = other.ref;
			other.ref = nullptr;
			return *this;
		}
		void swap(LSharedPtr& other){
			swap(ref, other.ref);
		}
		void reset(T* target = nullptr){
			if (ref){
				ref->reduce();
			}
			if (target != nullptr){
				ref = new Ref<T>(target);
			}
			else{
				ref = nullptr;
			}
		}//指向新的引用计数，引用计数指向新的node
		T& operator*(){
			if (ref){
				return *ref->get();
			}
			else{
				return *(T*)nullptr;
			}
		}
		T* operator->(){
			if (ref){
				return ref->get();
			}
			else{
				return (T*)nullptr;
			}
		}
		T* get(){
			if (ref){
				return ref->get();
			}
			else{
				return (T*)nullptr;
			}
		}
		int use_count(){
			if (ref){
				return ref->getCount();
			}
			else{
				return 0;
			}
		}
		bool unique(){
			if (ref){
				return ref->getCount() == 1;
			}
			else{
				return false;
			}
		}
		//判断当前智能指针是否和对象关联
		operator bool(){
			return ref != nullptr;
		}
	};
	//可以指定一个引用计数对象，在需要时
	/*class LweakPtr{

	};*/

	//可以指定一个引用计数对象，在需要时获得  shared_ptr
	/*无参构造，
	/传递一个shared_ptr构造
	拷贝构造,移动构造.拷贝赋值，移动赋值
	use_count()获得指定对象的引用计数(shared_ptr的计数)
	lock()  获得一个shared_ptr
	expired() 判断是否已经删除
	sawp()
	reset()
	*/
	template<class T>
	class LweakPtr{
		Ref<T>* ref = nullptr;
	public:
		LweakPtr() = default;
		LweakPtr(LSharedPtr<T>& other) :ref(other.ref){
			cout << "使用shread_构造一个weak的拷贝赋 值运算符" << endl;
			if (ref){
				ref->increase_w();
			}
		}
		LweakPtr(const LweakPtr<T>& other) :ref(other.ref){
			if (ref){
				ref->increase_w();
			}
		}
		LweakPtr(LweakPtr<T>&& other){
			swap(ref, other.ref);
		}
		LweakPtr<T>& operator = (const LweakPtr<T>& other){
			cout << "调用了weak的拷贝赋值运算符" << endl;
			if (ref){
				ref->reduce_w();
			}
			ref = other.ref;
			if (ref){
				ref->increase_w();
			}
			return *this;
		}
		LweakPtr<T>&  operator=(LweakPtr<T>&& other){
			cout << "调用了weak的移动赋值运算符" << endl;
			if (ref){
				ref->reduce_w();
			}
			ref = other.ref;
			other.ref = nullptr;
			return *this;
		}
		int use_count(){
			if (ref){
				return ref->getCount();
			}
			else{
				return 0;
			}
		}
		bool expired(){
			if (ref){
				return ref->getCount() > 0;
			}
			else{
				return false;
			}
		}
		LSharedPtr<T> lock(){
			LSharedPtr<T> tem(ref);
			return tem;
		}

		void sawp(LweakPtr<T>& other){
			swap(ref, other.ref);
		}
		void reset(){
			ref->reduce_w();
			ref = nullptr;
		}
	};
	template<class T, class ...args>
	LSharedPtr<T>
		make_Lshared(args... a){
			//将ref对象和T对象在一起创建。
			//创建一次ref对象，在new T对象
			LSharedPtr<T> t(new T(a...));
			return t;
		}


}
