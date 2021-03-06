#include <iostream>
//#include "llist_sol.h"
#include "llist.h"
#include "stack.h"
#include "queue.h"

using namespace std;

int main()
{
  Queue<int> mylist;
  mylist.push_back(5);
  mylist.push_back(6);
  mylist.push_back(7);
  cout << "Front item is: " << mylist.front() << endl;
  //cout << "Item at location 1 is " << mylist[1] << endl;
  //mylist.remove(6);
  //mylist.insert(0,4);
  //mylist.insert(3,8);
  cout << "List contents (and removal)" << endl;
  cout << "Size: " << mylist.size() << endl;
  while(!mylist.empty()){
    cout << mylist.front() << endl;
    mylist.pop_front();
  }
  mylist.pop_front();
  return 0;
}
