// domino.cpp
// Amiel Martin
// Sep 30 2006

// domino implementation
// TODO: finish writing purpose of this file, when I acutally figure out
// what it is


#include <string>
using std::string;

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

#include <cstdlib>
using std::size_t;

#include <vector>

#include <stdexcept>

// DominoBoard
// class to hold a domino board
// Invariants:
class DominoBoard {

  // *** DominoBoard: typedefs, enums, etc *** //
  public:
    typedef enum { EMPTY, HORIZ_BEGIN, HORIZ_END, VERT_BEGIN, VERT_END } dominostate;
    typedef enum { VERT, HORIZ } orientation;
    typedef std::vector<dominostate> BoardRow;
    typedef std::vector<BoardRow> Board;

  // *** DominoBoard: ctors, op=, dctor *** //
  public:
    // no default ctor, we need a size

    // ctor
    // Pre:
    // Post:
    DominoBoard(size_t size_x, size_t size_y)
      : size_x_(size_x), size_y_(size_y), board_(size_y, BoardRow(size_x, EMPTY) )
        , calls(0), maxdepth(0), loops(0)
    { }

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
    int domino_recurse(int numDominoes, int x, int y);


    void printstats(ostream & out) const {
      cout << "loops: " << loops << endl
        << "calls: " << calls << endl
        << "maxdepth: " << maxdepth << endl;
    }

    void print(ostream & out) const {
      for (Board::const_iterator i = board_.begin(); i != board_.end(); ++i) {
        for(BoardRow::const_iterator j = i->begin(); j != i->end(); ++j) {
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
      cout << endl;
    }

  // *** DominoBoard: Private Helper Functions *** //
  private:

    // place_domino
    // pre: x and y must be in range
    // post:
    bool place_domino(int x, int y, orientation);
    void remove_domino(int x, int y, orientation);

    void place_vert(int x, int y, dominostate state1, dominostate state2) {
      board_[y][x] = state1;
      board_[y+1][x] = state2;
    }

    void place_horiz(int x, int y, dominostate state1, dominostate state2) {
      board_[y][x] = state1;
      board_[y][x+1] = state2;
    }

  // *** DominoBoard: Data Members *** //
  private:
    int size_x_;
    int size_y_;
    Board board_;
  public:
    int calls;
    int maxdepth;
    int loops;
};



// place_domino
// pre: x and y must be in range
// post:
// this function needs to be totally rewritten
bool DominoBoard::place_domino(int x, int y, orientation orient) {
  if ( !(x < size_x_ && y < size_y_) )
    // TODO: fix this, it should never happen, but I like having lots of error
    // checking
    throw std::range_error("in DominoBoard::place_domino(int, int, orientation): x or y out of range");

  if (board_[y][x] != EMPTY)
    throw std::runtime_error("in DominoBoard::place_domino(int, int, orientation): tried to place a domino in a non-empty square"); // same here this could just be a precond


  if (orient == HORIZ && (x+1) < size_x_ && board_[y][x+1] == EMPTY) {
    place_horiz(x, y, HORIZ_BEGIN, HORIZ_END);
    return true;
  } else if (orient == VERT && (y+1) < size_y_ && board_[y+1][x] == EMPTY) {
    place_vert(x, y, VERT_BEGIN, VERT_END);
    return true;
  }
  //cout << "could not place domino in: x=" << x << " y=" << y << endl;
  return false;
}


// remove_domino
// remove a domino
// Pre:
  // x and y must be in range
  // and if orient is HORIZ, then x+1 < size_x_
  // and if orient is VERT, then y+1 < size_y_
// Post:
void DominoBoard::remove_domino(int x, int y, orientation orient) {
  if (orient == HORIZ && (x+1) < size_x_) { // && board_[y][x+1] == HORIZ_END) {
    place_horiz(x, y, EMPTY, EMPTY);
  } else if (orient == VERT && (y+1) < size_y_) { // && board_[y+1][x] == VERT_END) {
    place_vert(x, y, EMPTY, EMPTY);
  } else {
    throw std::runtime_error("in DominoBoard::remove_domino(int, int, orientation): could not remove domino");
  }
}




// domino_recurse
// Recursive
// the workhorse function to calculate how many possible domino tilings
// there are the specified board
int DominoBoard::domino_recurse(int numDominoes, int x, int y) {
  static int debugrecusiondepth = 0;
  maxdepth = (debugrecusiondepth > maxdepth) ? debugrecusiondepth : maxdepth ;
  ++calls;
  if (numDominoes * 2 == size_x_ * size_y_){
    print(cout);
    return 1; // we have a full solution
  }

  //if (x > size_x_ || y > size_y_)
  //  return 0;

  int count = 0; // succesful tries
  bool found = false;

  int j = x;
  for (int i = y; i < board_.size(); ++i, j = 0) {
    for ( ; j < board_[i].size(); ++j) {
      ++loops;

      /*cout << " in domino_recurse Point A: recursion depth is " << debugrecusiondepth << endl
        << "numDominoes = " << numDominoes << endl
        << "x = " << x << " and y = " << y << endl
        << "j = " << j << " and i = " << i << endl;
      print(cout);*/

      // try next place, this one is not empty
      if (board_[i][j] != EMPTY)
        continue;

      if (place_domino(j, i, VERT)) {
        ++debugrecusiondepth;
        count += domino_recurse(numDominoes + 1, j + 1, i);
        --debugrecusiondepth;
        found = true;
        remove_domino(j, i, VERT);
      }

      //cout << " in domino_recurse Point B: x = " << x << " and y = " << y << endl;
      //print(cout);

      if (place_domino(j, i, HORIZ)) {
        // not sure if we should try y+1?
        ++debugrecusiondepth;
        count += domino_recurse(numDominoes + 1, j + 1, i);
        --debugrecusiondepth;
        found = true;
        remove_domino(j, i, HORIZ);
      }
      
      //cout << " in domino_recurse Point C: x = " << x << " and y = " << y << " returning count = " << count << endl;

      if (found)
        return count;
    }
  }
  return count;
}







// domino
// interface to domino_recursive
int domino(int size_x, int size_y) {
  // if there are an odd number of squares on the board then there are
  // no possible tilings
  if ( (size_x * size_y) % 2 == 1)
    return 0;

  try {
    DominoBoard board(size_x, size_y);
//    return board.domino_recurse(0, 0, 0);
    int value = board.domino_recurse(0,0,0);
    board.printstats(cout);
    return value;

  } catch (std::runtime_error & e) { // this is really the wrong place for this, but for now...
    cout << "ERROR: " << e.what() << endl;
    return 0;
  }
}

