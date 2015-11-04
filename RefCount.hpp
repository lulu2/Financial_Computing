#ifndef REFC
#define REFC

template <typename T>
class RefCount{
public:
	RefCount(T* obj): ptrObj(obj), count(new int(1)){}
	RefCount(const RefCount& p): ptrObj(p.ptrObj), count(p.count){(*count)++;}
	RefCount & operator=(const RefCount &);
	~RefCount();
	int getCount(){return *count;} 

private:
	int* count;
	T* ptrObj;
};

template <typename T>
RefCount<T>::~RefCount<T>(){
	if (--(*count)== 0){
		delete count;
	}
}

template <typename T>
RefCount<T> & RefCount<T>::operator= (const RefCount<T> & rhs){
	++*rhs.count;
	if(--(*count) == 0){
		delete count;
	}
	ptrObj = rhs.ptrObj;
	count = rhs.count;
	return *this;
}

#endif
