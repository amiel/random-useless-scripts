// da3.h
// Amiel Martin
// Mon Sep 25 2006

// Assignment 3
// for cs 311

// this file contains 4 parts
// 1 doesThisThrow
//      returns true if its argument throws, returns false otherwise
// 2 printRev
//      prints a string in reverse to a stream
// 3 divideAll
//      given two iterators, it divides all items in the container by denom
// 4 sortDescendingInt
//      given two iterators, it sorts the container in descending order


#include <string>
using std::string; // for printRev

#include <ostream>
using std::ostream; // for printRev

#include <stdexcept>
// using std::range_error for divideAll

#include <algorithm>
// using std::sort and std::greater for sortDescendingInt



#ifndef DA3_H
#define DA3_H


// *** part 1 *** //

// doesThisThow
// template requirements: Function must be a callable function, or something
//      that acts like a function
// Pre: theFunc must act like a function
// Post: returns true if theFunc throws
// does not throw
template <typename Function>
bool doesThisThrow(Function theFunc) {
  bool ret = false;

  try {
    theFunc();
  } catch (...) {
    ret = true;
  }

  return ret;
}




// *** part 2 *** //

// printRev
// Recursive -- in the not so efficient way
// Pre: None
// Post: prints string printMe in reverse to the given stream
// does not throw
void printRev(ostream & theStream, const string & printMe) {
  int length = printMe.length();
  if (length == 0)
    return;

  printRev(theStream, printMe.substr(1,length));
  theStream << printMe[0];
}





// *** part 3 *** //

// divideAll
// divides all items in a container by denom
// template requirements:
//      ForwardIterator must be a forward iterator that
//      points to something that has op /=
//      Number must be something that can be a denominator
// Pre:
//      first to last must be a valid range
// Post: all items in between first and last will be divided by denom
// may throw std::range_error
template <typename ForwardIterator, typename Number>
void divideAll(ForwardIterator first, ForwardIterator last, const Number & denom) {
  if (denom == 0)
    throw std::range_error("in divideAll(ForwardIterator, ForwardIterator, const Number&): denominator may not be '0'");

  for( ; first != last; ++first)
    *first /= denom;
}






// *** part 4 *** //

// sortDescendingInt
// sorts a container in descending order
// template requirements: RandomAccessIterator must be a...
//              SURPRISE, it must be a random access iterator
//              specifically an iterator to a container of ints
// Pre: first to last must be a valid range
// Post: range will be in descending order
// does not throw
template <typename RandomAccessIterator>
void sortDescendingInt(RandomAccessIterator first, RandomAccessIterator last) {
  std::sort(first, last, std::greater<int>());
}


/*
// pollible generic version
template <typename RandomAccessIterator>
void sortDescendingInt(RandomAccessIterator first, RandomAccessIterator last) {
  typedef typename std::iterator<RandomAccessIterator>::value_type ValueType;
  std::sort(first, last, std::greater<ValueType>());
}
*/



#endif // #ifndef DA3_H
