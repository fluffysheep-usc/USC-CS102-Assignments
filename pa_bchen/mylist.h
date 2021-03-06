#ifndef MY_LIST_H
#define MY_LIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

 template <typename T> class MyList {
	public:
		MyList();
		MyList(int size);
		~MyList();
		void push_back(T item);
		bool remove(T val);
		int size();
		T& at(int position);
		T& operator[] (int position);
		T pop(int loc);
		
	private:
		int capacity; 	// how much the array can hold
		int sizeOf; 	// how much is in the array.
		T* data; 	// whatever data is stored in this list class.
};

template <typename T> MyList<T>::MyList(){
	
	sizeOf=0;		//sizeOf is 0 b/c there is nothing in data.
	capacity=1;		//capacity is set to 1.
	data = new T[capacity];	//Constructor initializes data to have 1 capacity.
}

template <typename T> MyList<T>::MyList(int sz){
	data = new T[sz];	//In case a list is created with a specific capacity
	capacity = sz;		//Capacity is set to however large the usr sets it
	sizeOf = 0;		// sizeOf is zero b/c nothing is in the actual array
}

template <typename T> MyList<T>::~MyList(){
				//Leave empty unless need to delete something
							
	delete data;
}

 template <typename T> void MyList<T>::push_back(T item){
	if (sizeOf<capacity&&sizeOf>=0){		//Check is data full?
		data[sizeOf] = item;		//If not full, add item to the back of last item in data.
		sizeOf++;			//Now there is one more item in data so increment sizeOf
		return ;			//Successfully pushed item to back of list.
	}
	else {
		T* temp = new T[capacity*2];	//data is full, must increase the capacity via temp! sizeOf is unchanged.
		capacity*=2;			//we double the capacity for efficiency reasons.
		for (int i=0; i<sizeOf; i++){	//iterate through all items in data and store in temp array.
			temp[i] = data[i];	
		}
		delete [] data;			//delete data for efficiency reasons.
		data = temp;			//now make data point to temp. Basically data = temp.
		data[sizeOf] = item;		//place the item behind the last item in the list.
		sizeOf++;			//Now there is one more item in data so increment sizeOf
		return ;			//Successfully pushed item to back of list.
	}	
	return ;				//Somehow failed to push item to back of list.
}

 template <typename T> int MyList<T>::size(){
	return sizeOf;				//return amt of items in list.
}

 template <typename T> T& MyList<T>::at(int position){
	if (position<sizeOf&&position>=0){				//make sure 'position' is valid.
		return data[position];					//if valid yes, return the item @ position
	}
	else throw invalid_argument("Out of bounds! mylist.h 69");	//if valid false, throw exception!
}

template <typename T> bool MyList<T>::remove(T val){
	for (int i=0; i<sizeOf; i++){			//Iterate through all items in array.
		if (val == data[i]){			//Look for the item that matches 'val'
			for (int j=i+1; j<sizeOf;j++){	//If there is an item 'val', shift all elements after val's
				data[j-1]=data[j];		//position down (to the left).
			}				//This ovewrites val.
			sizeOf--;			//Now that val is gone, decrement the sizeOf the list.
			return true;			//Successful remove.
		}
	}
	return false;					//Failed to find val object in list.
}

template <typename T> T& MyList<T>::operator[](int position){
	if (position<sizeOf&&position>=0){				//Is position valid in data?
		return data[position];					//if yes, return the item in the position.
	}
	else throw invalid_argument("Out of Bounds! mylist.h 89");	//otherwise throw an error.
}

template <typename T> T MyList<T>::pop(int loc){
	if (loc<0||loc>sizeOf){						//is 'loc' a valid location in data?
		throw invalid_argument("Out of Bounds! mylist.h 94");	//if no, throw an error.
	}
	T temp = data[loc];						//Otherwise temp store the item in data
	for(int j=loc+1; j<sizeOf;j++){					//Shift all elements after the location
		data[j-1]=data[j];						//to the left shrinking the list.
	}
	sizeOf--;							//item at loc is gone from list so dec sizeOf
	return temp;							//return the item that was removed stored in temp
}

#endif

