// binsearch4.cpp
// Glenn G. Chappell
// 29 Sep 2006
//
// For CS 311
// Binary Search
// Version #4: Iterative (tail recursion eliminated)
// Based on binsearch3.cpp (tail-recursive version)

#include <iostream>
using std::cout;
using std::endl;
#include <cstdlib>   // for std::size_t
#include <iterator>  // for std::distance, std::advance


// binSearch
// Does Binary Search on a range.
// Requirements on types:
//     FDIter must be a forward iterator type.
//     ValueType must be the value type of FDIter.
//     operator< must be a total order on ValueType.
// Pre:
//     [first, last) must be a valid range.
//     Values in the range must be sorted by < (ascending).
// Post:
//     Return is true if findMe was found (using equivalence) in range,
//      false otherwise.
template <typename FDIter, typename ValueType>
bool binSearch(FDIter first,      // Iterator to first item in range
               FDIter last,       // Iterator to one-past last item in range
               ValueType findMe)  // value to find
{
    while (true)  // Loop forever -- for tail recursion elimination
    {
        // Compute size of range
        std::size_t size = std::distance(first, last);

        // Base case
        if (size <= 1)
        {
            if (size == 0)  // Range has size 0
                return false;
            else            // Range has size 1
                return !(*first < findMe) && !(findMe < *first);
        }

        // Recursive case

        // Get iterator to middle position of range
        FDIter pivotIter = first;
        std::advance(pivotIter, size/2);

        if (findMe < *pivotIter)
            last = pivotIter;
        else
            first = pivotIter;
    }
    // Recursive call is gone, replaced by loop
    // return binSearch(first, last, findMe);
}


int main()
{
    // Set up array
    const int SIZE = 100000;
    int arr[SIZE];
    for (int i = 0; i < SIZE; ++i)
        arr[i] = 10*i;

    int value = 40;  // Value to search for

    // Do a search
    bool success = binSearch(arr, arr + SIZE, value);

    // Print result
    if (success)
        cout << value << " FOUND" << endl;
    else
        cout << value << " not found" << endl;
}
