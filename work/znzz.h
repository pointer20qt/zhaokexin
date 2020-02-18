
	template<class T> class L_uniquePtr{
		T* obj = nullptr;
	public:
		L_uniquePtr(T* ptr) :obj(ptr){
		}
		L_uniquePtr(const T&) = delete;
		L_uniquePtr() = default;
		~L_uniquePtr(){
			delete obj;
		}
		L_uniquePtr& operator=(const L_autoPtr<T>&) = delete;
		L_uniquePtr(L_autoPtr<T>&& ptr) :obj(ptr.release()){

		}
		L_uniquePtr& operator=(L_autoPtr<T>&& ptr){
			obj = ptr.release();
			return *this;
		}
		void reset(T* newPtr = nullptr){
			delete obj;
			obj = newPtr;
		}
		T* release(){
			auto temP = obj;
			obj = nullptr;
			return temP;
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
	//资源计数类
	template<class T>
	class Ref{
		//当前资源计数
		int r_count=0;
		T* object=nullptr;
	public:
		Ref(T* target):object(target){
			++r_count;
		}
		inline void increase(){
			r_count++;
		}
		inline void reduce(){
			r_count--;
			if (r_count == 0){
				delete object;
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
	
	template<class T> class LSharedPtr{
		Ref<T>* ref=nullptr;
	public:
		LSharedPtr() = default;
		~LSharedPtr(){
			if (ref){
				ref->reduce();
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
			swap(ref,other.ref);
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
			swap(ref,other.ref);
		}
		void reset(T* target=nullptr){
			if (ref){
				ref->reduce();
			}
			if (target != nullptr){
				ref = new Ref<T>(target);
			}
			else{
				ref = nullptr;
			}
		}
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
		//判断当前只能指针是否和对象关联
		operator bool(){
			return ref != nullptr;
		}
	};
	//可以指定一个引用计数对象，在需要时
	class LweakPtr{

	};
}
