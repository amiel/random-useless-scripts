// domino.cpp
// Amiel Martin
// Sep 30 2006

// domino implementation
// TODO: finish writing purpose of this file, when I acutally figure out
// TODO: finish docs
// TODO: use std::advance?
// what it is


// TODO: doc usage of includes and put any in header file?
#include <iostream>
using std::ostream;
using std::endl;

#include <cstdlib>
using std::size_t;

#include <vector>

// DominoBoard
// class to hold a domino board
// Invariants:
  // board_ is always a valid partial solution
// does not throw
class DominoBoard {

  // *** DominoBoard: typedefs, enums, etc *** //
  public:
    // different states that a square can be
    // the only real reason that we keep states more specific then !EMPTY is
    // for printing
    typedef enum { EMPTY, HORIZ_BEGIN, HORIZ_END, VERT_BEGIN, VERT_END } square_state;

    // each row is a list of squares
    typedef std::vector<square_state> BoardRow;

    // a board is a list of rows
    typedef std::vector<BoardRow> Board;

  // *** DominoBoard: ctors, op=, dctor *** //
  public:
    // no default ctor, we need a size

    // ctor
    // Pre: size_x and size_y are reasonable ( > 0 )
    // Post: sizes are set and we start with an empty board
    // Note: whenever size_x + size_y is not at most 13, expect very long run times
      // thank you Glenn G. Chappell for this rule of thumb
    DominoBoard(size_t size_x, size_t size_y)
      : size_x_(size_x), size_y_(size_y), board_(size_y, BoardRow(size_x, EMPTY) )
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
    // there are in the specified board
    // Pre:
      // for every square ( < x and < y ) or < y must be part of a solution
      // numDominoes must represent the ( number of squares != EMPTY ) * 2
    // Post: returns the number of possible domino tilings in a size_x_ by
      // size_y_ board
    int domino_recurse(int numDominoes, int x, int y);


    // print
    // Pre: none
    // Post: ostream out has a nice visual representation printed to it
    void print(ostream & out) const;

  // *** DominoBoard: Private Helper Functions *** //
  private:

    // has_tile
    // Pre: x and y must be in range
    // Post: returns true if space at x, y is not empty
    bool has_tile(int x, int y) const {
      return board_[y][x] != EMPTY;
    }
    
    // place_domino_vert
    // pre: x and y must be in range
    // post: returns true only if placing a tile vertically would not overlap
          // another tile, or fall off the board
    bool place_domino_vert(int x, int y);

    // place_domino_horiz
    // pre: x and y must be in range
    // post: returns true only if placing a tile horizontally would not overlap
          // another tile, or fall off the board
    bool place_domino_horiz(int x, int y);

    // remove_domino_vert
    // pre:
      // x, y and x, y + 1 must be in range
      // x, y and x, y + 1 must point to VERT_BEGIN, and VERT_END respectively
    // post: sets the x, y and x, y + 1 to EMPTY
    void remove_domino_vert(int x, int y) {
      board_[y][x] = EMPTY;
      board_[y+1][x] = EMPTY;
    }

    // remove_domino_horiz
    // pre:
      // x, y and x + 1, y must be in range
      // x, y and x + 1, y must point to HORIZ_BEGIN and HORIZ_END respectively
    // post: sets the x, y and x + 1, y to EMPTY
    void remove_domino_horiz(int x, int y) {
      board_[y][x] = EMPTY;
      board_[y][x+1] = EMPTY;
    }


  // *** DominoBoard: Data Members *** //
  private:
    const int size_x_; // width of board
    const int size_y_; // height of board
    Board board_; // 2D vector, containing square_stateS

};


// print
// Pre: none
// Post: ostream out has a nice visual representation printed to it
void DominoBoard::print(ostream & out) const {
  for (Board::const_iterator row = board_.begin(); row != board_.end(); ++row) {
    for(BoardRow::const_iterator square = row->begin(); square != row->end(); ++square) {
      switch (*square) {
        case HORIZ_BEGIN   : out << "<"; break;
        case HORIZ_END     : out << ">"; break;
        case VERT_BEGIN    : out << "^"; break;
        case VERT_END      : out << "v"; break;
        default: case EMPTY: out << "."; break;
      }
    }
    out << endl;
  }
  out << endl;
}


// place_domino_vert
// pre: x and y must be in range
// post: returns true only if placing a tile vertically would not overlap
      // another tile, or fall off the board
bool DominoBoard::place_domino_vert(int x, int y) {
  if ((y+1) >= size_y_ || has_tile(x, y) || has_tile(x, y+1))
    return false;

  board_[y][x] = VERT_BEGIN;
  board_[y+1][x] = VERT_END;
  return true;
}

// place_domino_horiz
// pre: x and y must be in range
// post: returns true only if placing a tile horizontally would not overlap
      // another tile, or fall off the board
bool DominoBoard::place_domino_horiz(int x, int y) {
  if ((x+1) >= size_x_ || has_tile(x, y) || has_tile(x+1, y))
    return false;

  board_[y][x] = HORIZ_BEGIN;
  board_[y][x+1] = HORIZ_END;
  return true;
}




// domino_recurse
// Recursive
// the workhorse function to calculate how many possible domino tilings
// there are in the specified board
// Pre:
  // for every square ( < x and < y ) or < y must be part of a solution
  // numDominoes must represent the ( number of squares != EMPTY ) * 2
// Post: returns the number of possible domino tilings in a size_x_ by
  // size_y_ board
int DominoBoard::domino_recurse(int numDominoes, int x, int y) {
  // thank you Glenn G. Chappell for this formula
  if (numDominoes * 2 == size_x_ * size_y_)
    return 1; // we have a full solution

  int count = 0; // succesful tries
  bool found = false;


  // place

  for (unsigned int row = y, square = x;
      row < board_.size();
      ++row, square = 0) {
    for ( ;
        square < board_[row].size();
        ++square) {

      // if there is already a domino tile here, then try next place
      if (has_tile(square, row))
        continue;

      if (place_domino_vert(square, row)) {
        count += domino_recurse(numDominoes + 1, square + 1, row);
        found = true;
        remove_domino_vert(square, row);
      }


      if (place_domino_horiz(square, row)) {
        count += domino_recurse(numDominoes + 1, square + 2, row);
        found = true;
        remove_domino_horiz(square, row);
      }
      

      // if we found a spot, don't keep on looking, our recursive calls should
      // have taken care of the rest of the possibilities
      // this makes a HUGE difference in run time
      if (found)
        return count;
    }
  }

  // this case should be if we never find a place for a domino, which should
  // always return 0, but this seems more correct to me
  return count;
}








// domino
// interface to DominoBoard::domino_recurse
// Pre: size_x and size_y are reasonable ( > 0 )
// Post: returns the number of possible domino tilings in a size_x by size_y board
// Note: whenever size_x + size_y is not at most 13, expect very long run times
      // thank you Glenn G. Chappell for this rule of thumb
// does not throw
int domino(int size_x, int size_y) {
  // if there are an odd number of squares on the board then there are
  // no possible tilings
  if ( (size_x * size_y) % 2 == 1)
    return 0;

    DominoBoard board(size_x, size_y);
    return board.domino_recurse(0, 0, 0);
}

