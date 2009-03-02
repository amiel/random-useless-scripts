// bubble_sort1.cpp
// Glenn G. Chappell
// 9 Oct 2006
//
// For CS 311
// Bubble Sort
// Version #1: Using an Array

#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>  // for std::swap


// bubbleSort
// Do Bubble Sort on a given array.
// Requirements on Types:
//     operator< must be a total order on T.
//     T must have a copy ctor and copy assignment.
// Pre:
//     p points to an array of at least n items of type T
// Post:
//     p[0 .. n-1] contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename T>
void bubbleSort(T p[], int n)
{
    for (int endMark = n; endMark >= 2; --endMark)  // Passes; exit when sorted
        // endMark is subscript of one-past end
    {
        bool sorted = true;
            // True if was sorted before this pass
        for (int i = 0; i+1 < endMark; ++i)
            // p[i], p[i+1] are current pair
        {
            // compare & maybe swap p[i], p[i+1]
            if (p[i+1] < p[i])  // Out of order?
            {
                std::swap(p[i], p[i+1]);
                sorted = false;
            }
        }
        if (sorted)  // Sorted? Done.
            break;
    }
}


// main
// Test function bubbleSort, array version
int main()
{
    const int SIZE = 11;
    int arr[SIZE] = { 5, 3, 2, 8, 5, 9, 10, 4, 6, 1, -4 };
    bubbleSort(arr, SIZE);
    for (int i = 0; i < SIZE; ++i)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}