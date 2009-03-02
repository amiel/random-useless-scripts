// heapalg.h
// Amiel Martin
// Nov 25 2006

// For CS 311
// Header for Heap algorithms
// inteface functions (there are others, but they are not defined as part of the interface):
//	heapTest(RAIter, RAIter) -- test if a range is a heap
//	heapMake(RAIter, RAIter) -- make a heap from a range
//	heapSort(RAIter, RAIter) -- given a heap, sort it
//	heapInsert(RAIter, RAIter) -- insert the last item in a range to a heap
//	heapDelete(RAIter, RAIter) -- delete the highest value from the heap, and make it
//        the last item in the range
//
// other functions defined in this file:
//	heapParent_
//	heapLeftChild_
//	heapRightChild_
//	trickleDown_


#ifndef HEAPALG_H
#define HEAPALG_H


#include <algorithm> // for std::swap and std::iter_swap



// heapParent_
// given an iterator, returns an iterator for the parent in a complete binary tree
// No-Throw Guarantee
// requirements on types: RAIter must be a Random Access Iterator
// does not throw
// pre: first through (last-1) is a valid range
// post: returns the iterator of the parent. if the root is given, the root is returned
template <typename RAIter>
inline RAIter heapParent_(RAIter first, RAIter child) {
  return first + ((child-first-1) / 2);
}


// heapLeftChild_
// given an iterator, returns an iterator for the left child in a complete binary tree
// No-Throw Guarantee
// requirements on types: RAIter must be a Random Access Iterator
// does not throw
// pre: none
// post: returns the iterator of the left child
template <typename RAIter>
inline RAIter heapLeftChild_(RAIter first, RAIter parent) {
  return first + (2 * (parent-first)) + 1;
}

// heapRightChild_
// given an iterator, returns an iterator for the right child in a complete binary tree
// No-Throw Guarantee
// requirements on types: RAIter must be a Random Access Iterator
// does not throw
// pre: none
// post: returns the iterator of the right child
template <typename RAIter>
inline RAIter heapRightChild_(RAIter first, RAIter parent) {
  return first + (2 * (parent-first)) + 2;
}

// trickleDown_
// helper function
// Basic Guarantee
// requirements on types: RAIter must be a Random Access Iterator to a type
//	that can be swaped and has operator <
// throws anything that RAIters value_type throws for copy
// pre:
//	first through (last-1) is a valid range
//	children of cur are semi-heaps
// post: cur and all its decendants form a heap
template <typename RAIter>
void trickleDown_(RAIter first, RAIter cur, RAIter last) /* throw */ {
  while (true) {
    RAIter left  =  heapLeftChild_(first, cur);
    RAIter right = heapRightChild_(first, cur);

    if (
        right < last &&		// if there is a right child AND
        *left < *right &&	// the right child is larger than the left child AND
        *cur < *right		// the right child is larger than cur
        ) {
      std::iter_swap(right, cur);
      cur = right;
    } else if(
        left < last &&	// if there is a left child AND
        *cur < *left	// the left child is larger than cur
        ) { // left child is larger
      std::iter_swap(left, cur);
      cur = left;
    } else { // either both children are smaller, or don't exist
      return;
    }
  }
}


// heapTest
// function to test weather or not a range is a valid heap
// No-Throw Guarantee
// requirements on types: RAIter must be a Random Access Iterator to a type with operator <
// does not throw
// pre:  first through (last-1) must be a valid range
// post: returns true if range is a heap
template <typename RAIter>
bool heapTest(RAIter first, RAIter last) {
  RAIter i = first;
  for (++i /* skip the root*/; i < last; ++i)
    if (*heapParent_(first, i) < *i)
      return false;
  return true;
}


// heapInsert
// Heap insert operation.
// Inserts *(last-1) into Heap [first, last-1].
// Basic Guarantee
// requirements on types: RAIter must be a Random Access Iterator to a type
//	that can be swaped and has operator <
// throws anything that RAIters value_type throws for copy
// pre: first through (last-2) must be a valid heap *(last-1) is the item to insert
// post: first through (last-1) is a heap
template<typename RAIter>
void heapInsert(RAIter first, RAIter last) {
   RAIter cur = last-1;   // iter of item to "trickle up"
    while (cur != first) {
        RAIter parent = heapParent_(first, cur);
        if (!(*parent < *cur))
            break;

        std::iter_swap(cur, parent);
        cur = parent;
    }
}


// heapDelete
// Heap deletion operation.
// Removes the largest item in the heap and places it in *(last-1)
// Basic Guarantee
// requirements on types: RAIter must be a Random Access Iterator to a type
//	that can be swaped and has operator <
// throws anything that RAIters value_type throws for copy
// pre: first through (last-1) is a valid heap
// post:
//	first through (last-2) is a valid heap and *(last-1) is what used to be on
//	top of the heap
template <typename RAIter>
void heapDelete(RAIter first, RAIter last)
{
  std::iter_swap(first, last-1);
  trickleDown_(first, first, last-1);
}


// heapMake
// creates a heap from a range
// Basic Guarantee
// requirements on types: RAIter must be a Random Access Iterator to a type
//	that can be swaped and has operator <
// throws anything that RAIters value_type throws for copy
// pre: first through (last-1) is a valid range
// post: first through (last-1) is a valid heap
template <typename RAIter>
void heapMake(RAIter first, RAIter last) {
  RAIter bar = last;
  for (--bar; bar >= first; --bar)
    trickleDown_(first, bar, last);
}




// heapSort
// takes a heap, leaves range sorted
// Basic Guarantee
// requirements on types: RAIter must be a Random Access Iterator to a type
//	that can be swaped and has operator <
// throws anything that RAIters value_type throws for copy
// pre: first through (last-1) is a valid heap
// post: first through (last-1) is sorted in ascending order
template <typename RAIter>
void heapSort(RAIter first, RAIter last) {
  for (; last != first; --last)
    heapDelete(first, last);
}


#endif // #ifndef HEAPALG_H
