// quicksort1.cpp
// Glenn G. Chappell
// 16 Oct 2006
//
// For CS 311
// Quicksort
// Version #1: Basic
// Uses forward iterators

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>  // For std::iter_swap


// partition
// Partitions a sequence about a given pivot.
// Returns the new pivot position.
// Requirements on Types:
//     FDIter must be a forward iterator type.
//     operator< must be a total order on the value type of FDIter.
// Pre:
//     [first, last) is a valid nonempty range.
//     pivotIter is an iterator in the range [first, last).
// Post:
//     [first, last) contains the same items as it did initially,
//      but now each ITEM before pivotIter has ITEM < *pivotIter,
//      and each ITEM after pivotIter has !(ITEM < *pivotIter).
//     pivotIter lies in [first, last) and references an item with
//      the same value as *pivotIter before the function call.
template <typename FDIter>
void partition(FDIter first, FDIter last, FDIter & pivotIter)
{
    // Put the pivot at the start of the list
    std::iter_swap(first, pivotIter);

    // Now "first" points to the pivot

    // Make the "left list": list of items less than pivot
    FDIter leftFinal = first;  // points to final item in left list
    FDIter check = first;      // item to check
    for (++check;              // start after pivot, iterate through list
         check != last;
         ++check)
    {
        if (*check < *first)                   // if item < pivot
        {
            ++leftFinal;                       // ... move up end mark
            std::iter_swap(leftFinal, check);  // ... and put in left list
        }
    }

    // Note new pivot position, for caller, and put pivot there
    pivotIter = leftFinal;
    std::iter_swap(first, pivotIter);
}


// quicksort
// Sorts a sequence, using Quicksort.
// Recursive.
// Requirements on Types:
//     FDIter must be a forward iterator type.
//     operator< must be a total order on the value type of FDIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by <.
template <typename FDIter>
void quicksort(FDIter first, FDIter last)
{
    // BASE CASE
    if (first == last)
        return;

    // RECURSIVE CASE
    FDIter pivotIter = first;
    // Do partition & recursive sorts
    partition(first, last, pivotIter);
    quicksort(first, pivotIter);
    ++pivotIter;
    quicksort(pivotIter, last);
}


// main
// Test function quicksort, iterator version
int main()
{
   const int SIZE = 11;
   int arr[SIZE] = { 5, 3, 2, 8, 5, 9, 10, 4, 6, 1, -4};
   quicksort(arr, arr+SIZE);
   for (int i = 0; i < SIZE; ++i)
      cout << arr[i] << " ";
   cout << endl;

   return 0;
}
