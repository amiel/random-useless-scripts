// quicksort2.cpp
// Glenn G. Chappell
// 18 Oct 2006
//
// For CS 311
// Quicksort
// Version #2: Improved
// Uses random-access iterators
//
// Improvements over basic version (quicksort1.cpp):
//   - Pivot chosen using median-of-three.
//   - Tail-recursion elimination trick used to reduce recursion depth and
//     space usage.
// Neither of the above are efficient with sequential-access data; thus, we
// require random-access iterators in function "quicksort". Function
// "partition" is unchanged from quicksort1.cpp.

#include <iostream>
using std::cout;
using std::endl;

#include <algorithm>  // For std::iter_swap
#include <cstdlib>    // For std::size_t


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
// Sorts a sequence, using Quicksort, with median-of-three pivot
//  selection.
// Recursive.
// Requirements on Types:
//     RAIter must be a random-access iterator type.
//     operator< must be a total order on the value type of RAIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by <.
template <typename RAIter>
void quicksort(RAIter first, RAIter last)
{
    while (true)  // Tail-recursion elimination trick
    {
        std::size_t size = last - first;

        // BASE CASE
        if (size <= 1)
            return;

        // RECURSIVE CASE

        // Put median-of-three in position pivotIter
        RAIter pivotIter = first + size/2;
        if (*pivotIter < *first)
            std::iter_swap(first, pivotIter);
        if (*(last-1) < *pivotIter)
        {
            std::iter_swap(pivotIter, last-1);
            if (*pivotIter < *first)
                std::iter_swap(first, pivotIter);
        }

        // Do partition & recursive sorts
        //  with larger "recursive" sort done via iteration
        partition(first, last, pivotIter);
        if (pivotIter - first < last - (pivotIter+1))
        {
            quicksort(first, pivotIter);
            first = pivotIter+1;
        }
        else
        {
            quicksort(pivotIter+1, last);
            last = pivotIter;
        }
        // quicksort(first, last);  // tail-recursion eliminated
    }
}


// main
// Test function quicksort (takes iterators)
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
