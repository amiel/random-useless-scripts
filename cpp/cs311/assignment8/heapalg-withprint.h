#include <iostream>
// heapalg.h
// Amiel Martin
// Nov 25 2006
//
// For CS 311
// Header for Heap algorithms

#ifndef HEAPALG_H
#define HEAPALG_H



#include <cstdlib>  // for std::size_t
#include <algorithm> // for std::distance



#include <cmath> // for std::pow
#include <ostream> // for std::ostream and std::endl
#include <iomanip> // for std::setw
// printHeap
// debugging function
// pre:
// post:
template <typename RAIter>
void printHeap(std::ostream & out, RAIter first, RAIter last) {
  const int WIDTH = 4;
  for (RAIter i = first ; i != last; ++i)
    out << std::setw(WIDTH) << *i;
  out << std::endl;

  if (!heapTest(first, last)) {
    out << "printHeap: not a heap, returning" << std::endl;
    return;
  }

  int h = 1;
  for (int x = 1; x < std::distance(first, last); ++h)
    x = h + x;

  out << "printHeap: Tree height: " <<  h-1 << std::endl;

  int height = h;

  int k = 0;
  for ( ; 0 < h; --h) {
    for (int z = 0; z < h; ++z)
      for (int y = 0; y < WIDTH; ++ y)
        out << " ";
    int l = height - h;
    for(int i = k; i < k+std::pow(float(2), l); ++i) {
      out << std::setw(WIDTH * h) << first[i];
      if (i > last-first) {
        out << std::endl;
        return;
      }
    }
    k = 2*k+1;
    out << std::endl;
  }
}


// leftChild
// given an index, returns the index of the left child in a complete binary tree
// call like this with iterators: leftChild(std::distance(first, my_iterator))
// pre: none
// post: returns the index of the left child
std::size_t leftChild(std::size_t parent) {
  return (2 * parent) + 1;
}

// rightChild
// given an index, returns the index of the right child in a complete binary tree
// pre: none
// post: returns the index of the right child
std::size_t rightChild(std::size_t parent) {
  return (2 * parent) + 2;
}


// heapParent
// given an iterator, returns an iterator for the left child in a complete binary tree
// No-Throw Guarantee
// requirements on types:
// pre: none
// post: returns the iterator of the left child
template <typename RAIter>
RAIter heapParent(RAIter first, RAIter child) {
  return first + (child-first-1)/2;
}


// leftChild
// given an iterator, returns an iterator for the left child in a complete binary tree
// No-Throw Guarantee
// requirements on types:
// pre: none
// post: returns the iterator of the left child
template <typename RAIter>
RAIter leftChild(RAIter first, RAIter parent) {
  return first + (2 * std::distance(first, parent)) + 1;
}

// rightChild
// given an iterator, returns an iterator for the right child in a complete binary tree
// No-Throw Guarantee
// requirements on types:
// pre: none
// post: returns the iterator of the right child
template <typename RAIter>
RAIter rightChild(RAIter first, RAIter parent) {
  return first + (2 * std::distance(first, parent)) + 2;
}

// trickleDown
// helper function
// requirements on types:
// ??? Guarantee
// pre:
// post:
template <typename RAIter>
void trickleDown_(RAIter first, RAIter me, RAIter last) /* throw */ {
  while (true) {
    RAIter left  =  leftChild(first, me);
    RAIter right = rightChild(first, me);

    if (right < last && *left < *right && *me < *right) {
      std::iter_swap(right, me);
      me = right;
    } else if(left < last && *me < *left ) {
      std::iter_swap(left, me);
      me = left;
    } else {
      return;
    }
  }
}


// heapTest
// function to test weather or not a range is a valid heap
// ??? Guarantee
// requirements on types:
// pre: 
// post: returns true if range is a heap
template <typename RAIter>
bool heapTest(RAIter first, RAIter last) {
  for (RAIter i = first; i < last; ++i)
    if (*heapParent(first, i) < *i)
      return false;
  return true;
}


// heapInsert
// Heap insert operation.
// Inserts *(last-1) into Heap [first, last-1].
// pre:
// post:
template<typename RAIter>
void heapInsert(RAIter first, RAIter last)
{
    std::size_t me = std::distance(first, last)-1;   // index of item to "trickle up"
    while (me != 0)
    {
        std::size_t parent = (me-1)/2; // index of my parent
        if (!(first[parent] < first[me]))
            break;

        std::swap(first[me], first[parent]);
        me = parent;
    }
}


// heapDelete
// Heap deletion operation.
// Removes the largest item in the heap and places it in *(last-1)
// pre:
// post:
template <typename RAIter>
void heapDelete(RAIter first, RAIter last)
{
  std::iter_swap(first, last-1);
  trickleDown_(first, first, last-1);
}


// heapMake
// creates a heap from a range
// pre:
// post:
template <typename RAIter>
void heapMake(RAIter first, RAIter last)
{
  RAIter bar = last;
  for (--bar; bar >= first; --bar)
    trickleDown_(first, bar, last);
}




// heapSort
// takes a heap, leaves range sorted
// requirements on types:
// ??? Guarantee
// pre:
// post:
template <typename RAIter>
void heapSort(RAIter first, RAIter last) {
  for (; last != first; --last)
    heapDelete(first, last);
}
#endif // #ifndef HEAPALG_H
