// bubble_sort2.cpp
// Glenn G. Chappell
// 9 Oct 2006
//
// For CS 311
// Bubble Sort
// Version #2: Using Forward Iterators

#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>  // for std::iter_swap


// bubbleSort
// Do Bubble Sort on a given range.
// Requirements on Types:
//     FDIter must be a forward iterator type.
//     operator< must be a total order on the value type of FDIter.
//     The value type of FDIter must have a copy ctor and copy assignment.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename FDIter>
void bubbleSort(FDIter first, FDIter last)
{
    // Check for empty range
    if (first == last)
        return;

    FDIter endMark = last;
    while (true)  // Passes; exit when sorted
    {
        bool sorted = true;  // True if was sorted before this pass
        FDIter iter1 = first;  // *iter1, *iter2 are current pair
        FDIter iter2 = first;
        ++iter2;               // Set iter2 to just past first
        while (iter2 != endMark)
        {
            // compare & maybe swap *iter1, *iter2
            if (*iter2 < *iter1)  // Out of order?
            {
                std::iter_swap(iter1, iter2);
                sorted = false;
            }
            // Move current pair to next pair
            iter1 = iter2;
            ++iter2;
        }
        if (sorted)  // Sorted? Done.
            break;

        // "Decrement" endMark
        endMark = iter1;
    }
}


// main
// Test function bubbleSort, iterator version
int main()
{
    const int SIZE = 11;
    int arr[SIZE] = { 5, 3, 2, 8, 5, 9, 10, 4, 6, 1, -4 };
    bubbleSort(arr, arr+SIZE);
    for (int i = 0; i < SIZE; ++i)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}