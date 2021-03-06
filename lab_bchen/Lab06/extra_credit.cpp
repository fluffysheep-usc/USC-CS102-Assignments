#include <iostream>
//#include "llist_sol.h"
#include "llist.h"
#include "stack.h"
#include "queue.h"

using namespace std;

//template <typename T>
void printStack(Stack<int>* stack){
	cout<<"Stack:"<<endl;
	for (int i=0; i<stack->size(); i++){
		cout<<stack->at(i)<<endl;
	}
	cout<<"-----------"<<endl;
}

//template <typename T>
void printQueue(Queue<int>* queue){
	cout<<"Queue:"<<endl;
	for (int i=0; i<queue->size(); i++){
		cout<<queue->at(i)<<endl;
	}
	cout<<"--------------"<<endl;
}

int main()
{
  Stack<int> my_stack;
  Queue<int> my_queue;
  
  int input=0;
  
  while(input!=5){

  cout<<"Commands:"<<endl;
  cout<<"1. Push to stack"<<endl;
  cout<<"2. Print and pop top of stack"<<endl;
  cout<<"3. Push_back to Queue"<<endl;
  cout<<"4. Print and pop front of Queue"<<endl;
  cout<<"5. Quit"<<endl;
  cin>>input;
  
  int c1=0;
  int c3=0;
  
  switch(input){
  	case 1: 
  		cout<<"Input an Integer:"<<endl;
  		c1 = 0;
  		cin>>c1;
  		my_stack.push(c1);
  	break;
  	case 2: 
  		printStack(&my_stack);
  		my_stack.pop();
  	break;
  	case 3: 
  		cout<<"Input an Integer:"<<endl;
  		c3 = 0;
  		cin>>c3;
  		my_queue.push_back(c3);
  	break;
  	case 4: 
  		printQueue(&my_queue);
  		my_queue.pop_front();
  	break;
  	case 5: break;
  }
  }
  
  return 0;
}
