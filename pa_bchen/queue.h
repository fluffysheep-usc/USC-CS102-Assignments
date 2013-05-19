#ifndef QUEUE
#define QUEUE
#include <stdexcept>
#include "llist.h"

//using namespace std;

template <typename T>
class Queue : public LList<T>{
  public:
  	 Queue();
  	~Queue();
  	int size() const;
  	void push_back(const T& value);
  	void pop_front();
  	T& front();
  	T& back();
  	bool empty() const;

};

template <typename T>
Queue<T>::Queue() : LList<T>(){
}

template <typename T>
Queue<T>::~Queue(){
	LList<T>::clear();	
}

template <typename T>
int Queue<T>::size() const {
	return LList<T>::size();
}

template <typename T>
void Queue<T>::push_back(const T& value){
	return LList<T>::push_back(value);
}

template <typename T>
void Queue<T>::pop_front (){
	LList<T>::pop_front();
}

template <typename T>
T& Queue<T>:: front(){
	return LList<T>::peek_front();
}

template <typename T>
T& Queue<T>:: back(){
	if (this->size_ >0)
	return this->tail_->val;
	//throw std::invalid_argument("queue.h 61: No Tail!");
}

template <typename T>
bool Queue<T>::empty() const {
	return LList<T>::empty();
}
#endif


