#include <iostream>
#include <iomanip>
#include <map>
#include <set>
#include <cmath>
#include <cstdlib>
#include "board.h"
using namespace std;


/* Init a board of given size and scramble it with numInitMoves 
 * by moving the space tile with a randomly chosen direction N, W, S, E
 * some of which may be invalid, in which case we skip that move 
 * 
 *  @param size Number of tiles for the game.  \
 *      Should be a perfect square (4, 16, 25)
 *  @param numInitMoves Number of tile moves to attempt to scramble the board
 *  @param seed Use to seed the random number generator (srand) 
 */
Board::Board(int size, int numInitMoves, int seed )
{
  size_ = size;
  tiles_ = new int[size_];
  int dim = static_cast<int>(sqrt(size_));
  srand(seed);
  for(int i=0; i < size_; i++){
    tiles_[i] = i;
  }
  int blankLoc = 0;
  for(int i=0; i < numInitMoves; i++){
    int r = rand()%4;
    int randNeighbor = -1;
    if(r == 0){
      int n = blankLoc - dim;
      if(n >= 0){
	randNeighbor = n;
      }
    }
    else if(r == 1){
      int w = blankLoc - 1;
      if(blankLoc % dim != 0){
	randNeighbor = w;
      }
    }
    else if(r == 2){
      int s = blankLoc + dim;
      if(s  < size_){
	randNeighbor = s;
      }
    }
    else {
      int e = blankLoc + 1;
      if(blankLoc % dim != dim-1){
	randNeighbor = e;
      }
    }
    if(randNeighbor > -1){
      tiles_[blankLoc] = tiles_[randNeighbor];
      tiles_[randNeighbor] = 0;
      blankLoc = randNeighbor;
    }
  }
}


/* Default Constructor. Constructs a 2x2 board solved Board.
 */
Board::Board()
{
  //Constructs a board of size 4.
  //Dynamically allocates tiles of 4.
  //Initializes Board to values making the board already solved.
  size_ = 4;
  tiles_ = new int [size_];
  for (int i=0; i<size_;i++){
  	tiles_[i] = i;
  }
}

/* Deep Copy Constructor. Constructs a deep copy of the Board. Dynamically allocates tiles.
 *  @param b A reference to the Board you want to copy using a deep copy.
 */
Board::Board(const Board &b){
  //Dynamically allocates tiles based on b's size.
  //Make the new board's size = to b's size.
  //Initializes the board to the way b's board is initialized.
  tiles_ = new int[b.getSize()];
  size_ = b.size_;
  for (int i =0; i<size_; i++){
  	tiles_[i] = b.tiles_[i];
  }
	
	
}

/* Another Deep Copy Constructor. Constructs a deep copy of the Board. Dynamically allocates tiles.
 *  @param tiles A pointer to the tiles list that you want to copy.
 *  @param size The size of the tile list you are passing in the first parameter.
 */
Board::Board(int *tiles, int size){
  //Dynamically allocates the tiles.
  //Sets the size of the new board to the size in the parameter.
  //Initializes the board to the way b's board is initialized.
  tiles_ = new int[size];
  size_ = size;
  for (int i=0; i<size;i++){
  	tiles_[i]=tiles[i];
  }
} 

/* Destructor. Destroys the dynamically created tiles.
 */
Board::~Board()
{
  //Delete anything dynamically allocated. In this case its tiles.
  delete [] tiles_;
}

/* Swaps tile with specified tile. Move will only move the tile in the given parameter if the tile is
 *  		 visually adjacent to the blank tile spot.
 *  @param tile The value of the tile you want to move on the board. Not the index.
 */
bool Board::move(int tile){
	//Moves Tile
	//1. Find Blank Location. Blank Location is 0. Find the tile location
	//2. Find if blank tile next to tile
	//3. Swap Blank with tile.
	//-----------
  //1. Finding the blank tile location and the tile location and storing them.
	int blankLoc = 0, tileLoc=0;
	for (int i=0; i<size_; i++){
		if (tiles_[i] == tile){
			tileLoc = i;
		}
		if (tiles_[i] == 0){
			blankLoc = i;
		}
	}
  //2. Check if the tile is vertically adjacent
  	int verticleCheck = abs(tileLoc-blankLoc);
  	//If vertically adjacent then swap the tiles.
	if (verticleCheck == (int)sqrt(size_)){
		tiles_[blankLoc]=tiles_[tileLoc];
		tiles_[tileLoc] = 0;
		return true;
	}
	//Checks if the tile is horizontally adjacent.
	else 
	//If on the left of the blank tile  and the blank mod is 0 (blank is on the left) cannot move left.
	if (tileLoc==blankLoc-1 && blankLoc%(int)sqrt(size_)!=0){
		tiles_[blankLoc]=tiles_[tileLoc];
		tiles_[tileLoc] = 0;
		return true;
	}
	else
	//If on the right of the blank tile and the blank mod is sqrt(size_)-1 (blank is on the right) cannot move right.
	if (tileLoc==blankLoc+1 && blankLoc%(int)sqrt(size_)!=(int)(sqrt(size_))-1){
		tiles_[blankLoc]=tiles_[tileLoc];
		tiles_[tileLoc] = 0;
		return true;
	}
	return false;
}

/* Creates a map of potential moves. Function finds the blank tile and looks at its adjacent members.
 *  @return Returns a copy of the map generated by potential moves which contains an integer key and a Board pointer.
 */
std::map<int, Board*> Board::potentialMoves(){

  	//1. Find the blank tile.
  	//2. Find its adjacent members and check if they are in the same row.
  	//3. Create a new board for each possibility.
  	//-------

	int blankLoc=0;
	std::map<int, Board*> boardList; //Map of the boards that we will eventually return.
//1. Finds the blank tile location and stores it
	for (int i=0; i<size_; i++){
		if (tiles_[i]==0){
			blankLoc = i;
			break;
		}
	}
	
//2. Checks the potential moves of up, down, left, right
	int directions[4] = {sqrt(size_), -sqrt(size_), -1, 1}; //This array represents the four directions (up, down, left right)
	
	for (int i=0; i < 4; i++){
		//Run through the array of directions. 'i' in this case is the direction we are currently looking at.
		int tileLoc=0;
		tileLoc = blankLoc - directions[i];
		//if tileLoc doesn't exist in the array, then continue to next one.
		if (tileLoc<0 || tileLoc>=size_){
			continue;
		}
		//Check if the 'i' tile is adj. vertically
  		int verticleCheck = abs(tileLoc-blankLoc);
  
		if (verticleCheck == (int)sqrt(size_)){
			//If it is adjacent vertically, let's create a new board that represents its movement possiblity.
			Board *newBoard = new Board(*this);
			//After creating a new board, change the tiles on that new board to the new possibility.
			newBoard->move(tiles_[tileLoc]);
			//Now put the board in the map.
			boardList[tiles_[tileLoc]] = newBoard;
		}	
		//If the tile is not adj. vertically, check if it is adj is horizontally
		else 
		//If on the left of the blank tile  and the blank mod is 0 (blank is on the left) cannot move left.
		if (tileLoc==blankLoc-1 && blankLoc%(int)sqrt(size_)!=0){
			//If it is adjacent horizontally to the left, let's create a new board that represents its movement possiblity.
			Board *newBoard = new Board(*this);
			//After creating a new board, change the tiles on that new board to the new possibility.
			newBoard->move(tiles_[tileLoc]);
			//put in map
			boardList[tiles_[tileLoc]] = newBoard;
		}
		else
		//If on the right of the blank tile and the blank mod is sqrt(size_)-1 (blank is on the right) cannot move right.
		if (tileLoc==blankLoc+1 && blankLoc%(int)sqrt(size_)!=(int)(sqrt(size_))-1){
			//If it is adjacent horizontally to the right, let's create a new board that represents its movement possiblity.
			Board *newBoard = new Board(*this);
			//After creating a new board, change the tiles on that new board to the new possibility.
			newBoard->move(tiles_[tileLoc]);
			//put in map
			boardList[tiles_[tileLoc]] = newBoard;
		}		
	}
	//Boardlist now contains all the potential boards.
	return boardList;
	
}

/* Checks if the Board is solved by comparing the values with the index. If the values of each tile are the same as the index
 * they are in then return true;
 *  @return Returns true if Board is solved. Returns false if Board is not.
 */
  bool Board::solved(){
  	//Do a comparison between the tile values and the indicies.
  	for (int i=0; i<size_; i++){
  		if (i!=tiles_[i]){
  			//If the value of the tile does not equal the value of the index then the board is not solved.
  			return false;
  		}
  	}
  	return true;
  }
/* Less than operator overload. Compares the first tile from each board that is not equal to the the tile of the other board
 *  in the same index.
 *  @param rhs Board on the right hand side of the equation when comparing two boards.
 *  @return Returns true if Board is less than the other Board. Returns false if not.
 */
bool Board::operator<(const Board& rhs) const
{
//Code provided to us.
  if(size_ < rhs.size_){
    return true;
  }
  bool val = false;
  for(int i=0; i < size_; i++){
    if(tiles_[i] < rhs.tiles_[i]){
       return true;
     }
     else if(tiles_[i] > rhs.tiles_[i]){
       return false;
     }
  }
  return val;
}
/* Getter function returning the tile list.
 *  @return Returns a pointer to the list of values in the board.
 */
 int* Board::getTiles() const{
	return tiles_;
}
/* Getter function returning the size of the tile list.
 *  @return Returns the size of the tile list.
 */
int Board::getSize() const{
	return size_;
}

/* Checks if the the current Board is equal to the Board in the parameter by comparing each of their values in the corresponding indicies.
 * @param rhs the right hand side of the board being compared to. 
 * @return Returns a pointer to the list of values in the board.
 */
bool Board::operator==(const Board& rhs) const{
	if (rhs.getSize() == getSize()){
	//Checks the size first. If the sizes are not equal then just return false.
		int* rhsTiles = rhs.getTiles();
		
		for (int i=0; i<getSize();i++){
			if (tiles_[i]!=rhsTiles[i]){
			//If anytile value in the corresponding index is not the same return false
				return false;
			}
		}
		//return true if the size and tile values are the same.
		return true;
	}
	//returns false if the board size is not the same.
	return false;
}
/* Comparison to check if the Boards are not equal to each other by calling the == operator overload.
 *  @param rhs The right hand side of the comparison.
 *  @return Returns false if the Boards are not equal to each other.
 */
bool Board::operator!=(const Board& rhs) const{
	if (rhs==(*this)){
	//see == operator for details.
		return true;
	}
	else return false;
}

/* Outputs the board by printing each row on separate lines and a space between each column.
 *  @param os A reference to the ostream like "cout"
 *  @param b A reference to the board you want to print out.
 *  @return Returns a reference ostream allowing output functions like cout to utilize the << function.
 */
std::ostream& operator<<(std::ostream &os, const Board &b){
	int *tiles = b.getTiles(); //get the tile list
	int size = b.getSize();    //get the size of the tile list.
	int counter =0;            //counter used to figure out what index you are on.
	
	for (int i=0; i<sqrt(size); i++){
	//You only loop to the sqrt(size) to print out the columns.
		for (int j=0; j<sqrt(size); j++){
		// You only loop to the sqrt(size) to print out the rows.
			if (tiles[counter]==0){
			//Do not print the zero tile. That is our blank tile.
				os<<setw(int(log10(b.size_-1))+2)<<" ";
			}
			else{
			//Print out the rows/columns with beautiful spacing except the zero.
				os<<setw(int(log10(b.size_-1))+2)<<tiles[counter];
			}
			//Add one to the counter because the counter is our index.
			counter++;
		}
		os<<endl;
	}
	//Return the stream that has been constructed.
	return os;
}


