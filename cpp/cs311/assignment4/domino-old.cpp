// domino.cpp
// Amiel Martin
// Sep 30 2006

// domino implementation
// TODO: finish writing purpose of this file, when I acutally figure out
// what it is



#include <iostream>
using std::ostream;
using std::cout;
using std::endl;



#include <cstdlib>
using std::size_t;


#include <vector>
using std::vector;

// DominoPiece
// 
class DominoPiece {
  // *** DominoPiece: ctors, op=, dctor, typdefs, etc *** //
  public:
    typedef enum { VERT, HORIZ } orientation;

    // no default ctor, we have no set funcs

    // ctor
    // Pre: x and y must be in range, this should be checked by DominoBoard
    // Post:
    DominoPiece(int x, int y, orientation orient)
      : x1_(x),
        y1_(y),
        x2_( orient == HORIZ ? x + 1 : x ),
        y2_( orient == VERT  ? y + 1 : y ),
        orientation_(orient)
    { }

    // use the default big three, they should suffice

  private:
    int x1_, y1_; // coordinates for one half of the piece
    int x2_, y2_; // coordinates for the other half
    orientation orientation_;
};


// DominoBoard
// class to hold a domino board
// Invariants:
class DominoBoard {

  // *** DominoBoard: typedefs, enums, etc *** //
  public:
    typedef enum { EMPTY, HORIZ_BEGIN, HORIZ_END, VERT_BEGIN, VERT_END } domino;

  // *** DominoBoard: ctors, op=, dctor *** //
  public:
    // no default ctor, we need a size

    // ctor
    // Pre:
    // Post:
    DominoBoard(size_t size_x, size_t size_y)
      : size_x_(size_x), size_y_(size_y), board_(size_y, vector<domino>(size_x,EMPTY) ) { }

  private:
    // use default op= and copy ctor
    // but it might be best not to use them,
    DominoBoard(const DominoBoard &);
    DominoBoard operator = (const DominoBoard &);
      

  // *** DominoBoard: Public Functions *** //
  public:

    // domino_recurse
    // Recursive
    // the workhorse function to calculate how many possible domino tilings
    // there are the specified board
    int domino_recurse(int x, int y);

    void print(ostream & out) {
      for (vector< vector<domino> >::const_iterator i = board_.begin(); i != board_.end(); ++i) {
        for(vector<domino>::const_iterator j = i->begin(); j != i->end(); ++j) {
          switch (*j) {
            case HORIZ_BEGIN   : cout << "<"; break;
            case HORIZ_END     : cout << ">"; break;
            case VERT_BEGIN    : cout << "^"; break;
            case VERT_END      : cout << "v"; break;
            default: case EMPTY: cout << "."; break;
          }
        }
        cout << endl;
      }
    }

  // *** DominoBoard: Private Helper Functions *** //
  private:

    // place_domino
    // pre: x and y must be in range
    // post:
    bool place_domino(int x, int y, DominoPiece::orientation);
    bool remove_domino(int x, int y, DominoPiece::orientation);
    bool place_remove_domino(int x, int y, DominoPiece::orientation vert, domino);

  // *** DominoBoard: Data Members *** //
  private:
    int size_x_;
    int size_y_;
    vector< vector<domino> > board_;
};

// domino
// interface to domino_recursive
int domino(int size_x, int size_y) {
  // if there are an odd number of squares on the board then there are
  // no possible tilings
  if ( (size_x * size_y) % 2 == 1)
    return 0;



  DominoBoard board(size_x, size_y);
  return board.domino_recurse(0, 0);
}



// place_domino
// pre: x and y must be in range
// post:
// this function needs to be totally rewritten
bool DominoBoard::place_domino(int x, int y, DominoPiece::orientation orient) {
  if ( !(x < size_x_ && y < size_y_) )
    // TODO: fix this, it should never happen, but I like having lots of error
    // checking
    throw;

  if (board_[y][x] != EMPTY)
    return false;

  if (orient == DominoPiece::HORIZ && (y+1) < size_y_ && board_[y+1][x] == EMPTY) {
      board_[y][x] = HORIZ_BEGIN;
      board_[y][x+1] = HORIZ_END;
      return true;
    } else if (orient == DominoPiece::VERT && (x+1) < size_x_ && board_[y][x+1] == EMPTY) {
      board_[y][x] = VERT_BEGIN;
      board_[y+1][x] = VERT_END;
      return true;
    }
  return false;
}





// domino_recurse
// Recursive
// the workhorse function to calculate how many possible domino tilings
// there are the specified board
int DominoBoard::domino_recurse(int x, int y) {
  int count = 0; // succesful tries
  if (x > size_x_ || y > size_y_)
    return 0;

  while(true) {
    cout << " in domino_recurse: x = " << x << " and y = " << y << endl;
    print(cout);
    // AMIEL, START HERE
    if (place_domino(x, y, DominoPiece::VERT))
      count += domino_recurse(x, y + 1);

    cout << " in domino_recurse Point B: x = " << x << " and y = " << y << endl;
    print(cout);

    if (place_domino(x, y, DominoPiece::HORIZ))
      count += domino_recurse(x + 1, y);

    //remove_domino(x, y);
  }
  return count;
}
