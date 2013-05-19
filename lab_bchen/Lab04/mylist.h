#include <iostream>
#include <stdexcept>

using namespace std;

 template <typename T> class MyList {
	public:
		MyList();
		MyList(int size);
		~MyList();
		bool push_back(T item);
		bool remove(T val);
		int size();
		T& at(int position);
		T& operator[] (int position);
		T pop(int loc);
		
	private:
		int capacity; // how much the array can hold
		int sizeOf; // how much is in the array.
		T* data;
};

template <typename T> MyList<T>::MyList(){
	data = new T[1];
	sizeOf=0;
	capacity=1;
}

template <typename T> MyList<T>::MyList(int sz){
	data = new T[sz];
	capacity = sz;
	sizeOf = 0;	
}

template <typename T> MyList<T>::~MyList(){

}

 template <typename T> bool MyList<T>::push_back(T item){
	if (sizeOf<capacity&&sizeOf>0){
		data[sizeOf] = item;
		sizeOf++;
		return true;
	}
	else {
		T* temp = new T[capacity*2];
		capacity*=2;
		for (int i=0; i<sizeOf; i++){
			temp[i] = data[i];
		}
		delete []data;
		data = temp;
		data[sizeOf] = item;
		sizeOf++;
		return true;
	}
	return false;
}

 template <typename T> int MyList<T>::size(){
	return sizeOf;
}

 template <typename T> T& MyList<T>::at(int position){
	if (position<sizeOf&&position>=0){
		return data[position];
	}
	else throw invalid_argument("Index out of bounds error!");
}

template <typename T> bool MyList<T>::remove(T val){
	for (int i=0; i<sizeOf; i++){
		if (val == data[i]){
			for (int j=i+1; j<sizeOf;j++){
				data[j-1]=data[j];
			}
			sizeOf--;
			return true;
		}
	}
	return false;
}

template <typename T> T& MyList<T>::operator[](int position){
	if (position<sizeOf&&position>=0){
		return data[position];
	}
	else throw invalid_argument("Index out of bounds error!");
}

template <typename T> T MyList<T>::pop(int loc){
	if (loc<0||loc>sizeOf){
		throw invalid_argument("Index out of bounds error!");
	}
	T temp = data[loc];
	for(int j=loc+1; j<sizeOf;j++){
		data[j-1]=data[j];
	}
	sizeOf--;
	return temp;
}

