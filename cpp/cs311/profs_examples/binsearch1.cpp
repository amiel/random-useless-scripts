// binsearch1.cpp
// Glenn G. Chappell
// 25 Sep 2006
//
// For CS 311
// Binary Search
// Version #1: Recursive

#include <iostream>
using std::cout;
using std::endl;

#include <cstdlib> // for std::size_t

#include <iterator> // for std::distance

// binSearch
// Does a binary search on a range.
// Recursive.
// Requirements on types:
//     RAIter must be a random-access iterator type.
//     ValueType must be the value type of RAIter.
//     ValueType must be copy-constructable.
//     operator< must be a total order on ValueType.
//     ValueType must be equality comparable (with operator==).
// Pre:
//     [first, last) must be a valid range.
//     Values in the range must be sorted by < (ascending).
// Post:
//     Return is true if findMe was found in range, false otherwise.
template <typename RAIter, typename ValueType>
bool binSearch(RAIter first,      // Iterator to first item in range
               RAIter last,       // Iterator to one-past last item in range
               const ValueType & findMe)  // value to find
{

  std::size_t size = std::distance(first, last);
    // Base case
    if (size <= 1)
    {
        if ( size == 0 )  // Range has size 0
        {
            return false;
        }
        else                // Range has size 1
        {
            return !(*first < findMe) && !(findMe < *first);
        }
    }

    // Recursive case
    else
    {
        // Get iterator to middle position of range
        RAIter pivotIter = first;
        std::advance(pivotIter, size/2);

        if (findMe < *pivotIter)
            return binSearch(first, pivotIter, findMe);
        else
            return binSearch(pivotIter, last, findMe);
    }
}


int main()
{
    // Set up array
    const int SIZE = 1000000;
    int arr[SIZE];
    for (int i = 0; i < SIZE; ++i)
        arr[i] = 10*i;

    int value = 41;  // Value to search for

    // Do a search
    bool success = binSearch(arr, arr + SIZE, value);

    // Print result
    if (success)
        cout << value << " FOUND" << endl;
    else
        cout << value << " not found" << endl;
}
