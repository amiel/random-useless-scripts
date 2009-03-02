// domino.h
// Amiel Martin
// Sep 30 2006

// for Assignment 4 (DA4)
// for cs311
// a package that computes the number of domino tilings for a given
// rectangular board


#ifndef DOMINO_H
#define DOMINO_H

// domino
// interface to DominoBoard::domino_recurse
// Pre: size_x and size_y are reasonable ( > 0 )
// Post: returns the number of possible domino tilings in a size_x by size_y board
// Note: whenever size_x + size_y is not at most 13, expect very long run times
  // thank you Glenn G. Chappell for this warning
// does not throw
int domino(int size_x, int size_y);

#endif // #ifndef DOMINO_H
