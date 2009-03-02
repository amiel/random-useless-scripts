// domino.cpp
// Amiel Martin
// Sep 30 2006

// domino implementation
// TODO: finish writing purpose of this file, when I acutally figure out
// what it is


#include <iostream>
using std::ostream;
using std::endl;

#include <cstdlib>
using std::size_t;

#include <vector>

#include <stdexcept>

#include <iterator>

// DominoBoard
// class to hold a domino board
// Invariants:
  // board_ is always a valid partial solution
class DominoBoard {

  // *** DominoBoard: typedefs, enums, etc *** //
  public:
    typedef enum { EMPTY, HORIZ_BEGIN, HORIZ_END, VERT_BEGIN, VERT_END } dominostate;
    typedef enum { VERT, HORIZ } orientation;
    typedef std::vector<dominostate> BoardRow;
    typedef std::vector<BoardRow> Board;

    typedef Board::iterator iterate_rows;
    typedef Board::const_iterator const_iterate_rows;
    typedef BoardRow::iterator iterate_items;
    typedef BeardRow::const_iterator const_iterate_items;


  // *** DominoBoard: ctors, op=, dctor *** //
  public:
    // no default ctor, we need a size

    // ctor
    // Pre:
    // Post:
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
    // there are the specified board
    int domino_recurse(int numDominoes, Board::iterator, BoardRow::iterator);

    int domino() {
      return domino_recurse(0, board_.begin(), board_.begin()->begin());
    }

    void print(ostream & out) const;

  // *** DominoBoard: Private Helper Functions *** //
  private:

    // has_tile
    // Pre: x and y must be in range
    // Post: returns true if space at x, y is not empty
    bool has_tile(Board::const_iterator item) const {
      return *item != EMPTY;
    }
    
    // place_domino_vert
    // pre: x and y must be in range
    // post: returns true only if placing a tile vertically would not overlap
          // another tile, or fall off the board
    bool place_domino_vert(Board::iterator, BoardRow::iterator);

    // place_domino_horiz
    // pre: x and y must be in range
    // post: returns true only if placing a tile horizontally would not overlap
          // another tile, or fall off the board
    bool place_domino_horiz(Board::iterator, BoardRow::iterator);

    // remove_domino_vert
    // pre:
      // x, y and y + 1 must be in range
      // x, y and x, y + 1 must point to VERT_BEGIN, and VERT_END respectively
    // post: sets the x, y and x, y + 1 to EMPTY
    void remove_domino_vert(Board::iterator row, BoardRow::iterator item) {
      Board::iterator row2 = row;
      ++row2;
      BoardRow::iterator item2 = ( row2 + std::distance(row->begin(), item) );

      if (row2 == board_.end()) // this is a precond, we could get rid of it?
        throw(std::range_error("remove_domino_vert"));

      *item = EMPTY;
      *item2 = EMPTY;
    }

    // remove_domino_horiz
    // pre:
      // x, y and x + 1 must be in range
      // x, y and x + 1, y must point to HORIZ_BEGIN and HORIZ_END respectively
    // post: sets the x, y and x + 1, y to EMPTY
    void remove_domino_horiz(Board::iterator row, BoardRow::iterator item) {
      if (item2 == row->end()) // this is a precond, we could get rid of it?
        throw(std::range_error("remove_domino_horiz"));

      *item = EMPTY;
      *item2 = EMPTY;
    }


        

  // *** DominoBoard: Data Members *** //
  private:
    int size_x_;
    int size_y_;
    Board board_;
};


// print
// Pre: none
// Post: ostream out has a nice visual representation printed to it
void DominoBoard::print(ostream & out) const {
  for (Board::const_iterator row = board_.begin(); row != board_.end(); ++row) {
    for(BoardRow::const_iterator item = row->begin(); item != row->end(); ++item) {
      switch (*item) {
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
// also pre: row must not be the last row
// also pre: item must be in row
// post: returns true only if placing a tile vertically would not overlap
      // another tile, or fall off the board
bool DominoBoard::place_domino_vert(Board::iterator row, BoardRow::iterator item) {
  Board::iterator row2 = row;
  ++row2;
  BoardRow::iterator item2 = ( row2 + std::distance(row->begin(), item) );

  if (row2 == board_.end() || has_tile(item) || has_tile(item2))
    return false;

  *item = VERT_BEGIN;
  *item2 = VERT_END;
  return true;
}

// place_domino_horiz
// pre: x and y must be in range
// post: returns true only if placing a tile horizontally would not overlap
// another tile, or fall off the board
bool DominoBoard::place_domino_horiz(Board::iterator row, BoardRow::iterator item) {
  BoardRow::iterator item2 = item;
  ++item2;
  if (item2 == row->end() || has_tile(item) || has_tile(item2))
    return false;

  *item = HORIZ_BEGIN;
  *item2 = HORIZ_END;
  return true;
}



// domino_recurse
// Recursive
// the workhorse function to calculate how many possible domino tilings
// there are the specified board
  int DominoBoard::domino_recurse(int numDominoes, Board::iterator startrow, BoardRow::iterator startitem) {
    if (numDominoes * 2 == size_x_ * size_y_)
      return 1; // we have a full solution

    int count = 0; // succesful tries
    bool found = false;


    for (Board::iterator row = startrow, BoardRow::iterator item = startitem;
        row < board_.end();
        ++row, item = row->begin()) {
      for ( ;
          item < row->end();
          ++item) {

        // if there is already a domino tile here, then try next place
        // this could be omited, but I think it will speed up, so that we don't
        // have to call place_domino_vert and place_domino_horiz, to continue
        // but I am thinking now that this might actually be slower
        if (has_tile(item))
          continue;

        if (place_domino_vert(item, row)) {
          count += domino_recurse(numDominoes + 1, item + 1, row);
          found = true;
          remove_domino_vert(item, row);
        }


        if (place_domino_horiz(item, row)) {
          // not sure if we should try y+1?
          count += domino_recurse(numDominoes + 1, item + 1, row);
          found = true;
          remove_domino_horiz(item, row);
        }


        // if we found a spot, don't keep on looking, our recursive calls should
        // have taken care of the rest of the possibilities
        // this makes a HUGE difference in run time
        if (found)
          return count;
      }
    }
    // this case should be if we never find a place for a domino, which should
    // always return 0, but theoretically, everything should work without the
    // if(found) statement above if this still returns count
    return count;
  }







// domino
// interface to domino_recursive
int domino(int size_x, int size_y) {
  // if there are an odd number of squares on the board then there are
  // no possible tilings
  if ( (size_x * size_y) % 2 == 1)
    return 0;

  DominoBoard board(size_x, size_y);
  return board.domino();
}

