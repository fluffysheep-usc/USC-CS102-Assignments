#include "puzzle_move.h"
#include "pmminlist.h"

/*
 * Default Constructor that does nothing :<
 */
PMMinList::PMMinList() : slist_()
{

}

/*
 * Destructor that does nothing :<
 */
PMMinList::~PMMinList()
{

}

/*
 * Adds the value val to the internal list in sorted
 * order from smallest to largest (if 
 * @param val Value to add to the sorted PuzzleMove list
 * @return nothing
 */
void PMMinList::push(PuzzleMove* pm)
{
  std::list<PuzzleMove*>::iterator it = slist_.begin();
 
  //---- Add your implementation to iterate through the list
  //---- to find the correct location to insert pm and then
  //---- use the insert() method of std::List to insert it
  //---- See http://www.cplusplus.com/reference/list/list/insert/
 
  if (slist_.size()==0){
  //If there is nothing in the list then just push the item onto the list. Loop.
  	slist_.push_front(pm);
  	return;
  }

 while(it!=slist_.end()){
 //If there is something in the list, then go through the list.
  	if (*pm < **it){
  	//Once you find that the puzzle move pm is smaller than the puzzle move your iterator is pointing to.
  	//Insert the puzzle move pm at your iterator's position.
  	//Then return so that you don't have to keep going through the rest of the list.
  		slist_.insert(it,pm);
  		return;
  	}
  	//Increment it to traverse through the list.
  	++it;
  }
  
  slist_.push_back(pm);
}

/*
 * Adds the value val to the internal list in sorted
 * order from smallest to largest
 * @param val Value to add to the sorted PuzzleMove list
 * @return nothing
 */
void PMMinList::pop()
{
  slist_.pop_front();
}

/*
 * Adds the value val to the internal list in sorted
 * order from smallest to largest
 * @param val Value to add to the sorted PuzzleMove list
 * @return reference to the minimum-scored PuzzleMove*
 */
PuzzleMove* PMMinList::top()
{
  return slist_.front();
}

