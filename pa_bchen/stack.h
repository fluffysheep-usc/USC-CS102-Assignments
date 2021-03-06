#ifndef STACK
#define STACK
#include <stdexcept>
#include "llist.h"

//using namespace std;

template <typename T>
class Stack : public LList<T>{
  public:
  	 Stack();
  	~Stack();
  	int size() const;
  	void push(const T& value);
  	void pop();
  	T& top();
  	bool empty() const;
  
 // private:

};

template <typename T>
Stack<T>::Stack() : LList<T>(){
}

template <typename T>
Stack<T>::~Stack(){
	this->clear();	
}

template <typename T>
int Stack<T>::size() const {
	return LList<T>::size();
}

template <typename T>
void Stack<T>::push(const T& value){
	return this->push_back(value);
}

template <typename T>
void Stack<T>::pop (){
	//cout<<"HELLO!"<<endl;
	this->pop_back();
}

template <typename T>
T& Stack<T>:: top(){
	try{return LList<T>::peek_back();}
	catch (std::invalid_argument e) {
		throw std::invalid_argument("stack.h 72 No Back. Error");
	}
}

template <typename T>
bool Stack<T>::empty() const {
	return LList<T>::empty();
}
#endif



