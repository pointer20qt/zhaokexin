#pragma once
//ģ�廯�����Խ����������Ͳ���
//���췽������ֵһ��ָ��
//�����������ͷ�ָ��
//����׼�ĸ��ƹ��죨ת���ڲ�ָ�����Ȩ��
//����׼�ĸ��Ƹ�ֵ��ת���ڲ�ָ�����Ȩ��
//reset  �ͷ�֮ǰ�ģ���ȡ�µ�ָ��
//release  �ͷſ���Ȩ������ָ��
//operator*()  ģ��ָ����ʷ���
//operator->()  ģ��ָ���ͷ��ʽ���ʷ���
//get()  ���ָ��ָ���ָ��
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

//�����ռ䣺Ϊ�˽���������Ϳ⺯������ͬ������
namespace zzz
{
	//��Դ������
	template<class T>
	class Ref{
		//��ǰ��Դ����
		int r_count = 0;
		//��ǰ������ָ�����
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
				//Ϊʲô112��Ҫ�ж�w_count�Ƿ�Ϊ0 ��
				if (w_count == 0){
					delete this;
				}
			}
		}
		inline void reduce_w(){
			w_count--;
			//ΪʲôҪ�ж�����Ҫ����r_count==0
			if (w_count == 0 && r_count == 0){
				delete this;
			}
		}
		//��öԶ���
		T* get(){
			return object;
		}
		int getCount(){
			return r_count;
		}
	};
	//shared����ָ����Ҫ�ķ���
	/*
	�޲ι��죬����������ָ�빹�죬�������죬�ƶ����죬������ֵ���ƶ���ֵ,����
	reset(T*)�滻���� reset() ���ٶ���
	operator*() operator->()
	get()�����ָ��
	use_count() ������ü���
	unique() �жϵ�ǰ�Ƿ�Ψһ  use_count()==1
	operator bool() �Ƿ��������
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
		}//ָ���µ����ü��������ü���ָ���µ�node
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
		//�жϵ�ǰ����ָ���Ƿ�Ͷ������
		operator bool(){
			return ref != nullptr;
		}
	};
	//����ָ��һ�����ü�����������Ҫʱ
	/*class LweakPtr{

	};*/

	//����ָ��һ�����ü�����������Ҫʱ���  shared_ptr
	/*�޲ι��죬
	/����һ��shared_ptr����
	��������,�ƶ�����.������ֵ���ƶ���ֵ
	use_count()���ָ����������ü���(shared_ptr�ļ���)
	lock()  ���һ��shared_ptr
	expired() �ж��Ƿ��Ѿ�ɾ��
	sawp()
	reset()
	*/
	template<class T>
	class LweakPtr{
		Ref<T>* ref = nullptr;
	public:
		LweakPtr() = default;
		LweakPtr(LSharedPtr<T>& other) :ref(other.ref){
			cout << "ʹ��shread_����һ��weak�Ŀ����� ֵ�����" << endl;
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
			cout << "������weak�Ŀ�����ֵ�����" << endl;
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
			cout << "������weak���ƶ���ֵ�����" << endl;
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
			//��ref�����T������һ�𴴽���
			//����һ��ref������new T����
			LSharedPtr<T> t(new T(a...));
			return t;
		}


}
