// selection_sort.cpp
// Glenn G. Chappell
// 9 Oct 2006
//
// For CS 311
// Selection Sort on an Array

#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>  // for std::swap


// selectionSort
// Do Selection Sort on a given array.
// Requirements on Types:
//     operator< must be a total order on T.
//     T must have a copy ctor and copy assignment.
// Pre:
//     p points to an array of at least n items of type T
// Post:
//     p[0 .. n-1] contains the same items as it did initially,
//      but now sorted by <.
template <typename T>
void selectionSort(T p[], int n)
{
    for (int endMark = n; endMark >= 2; --endMark)  // Passes
        // endMark is subscript of one-past end
    {
        // Find the item that goes in position endMark-1
        int biggest = 0;  // Holds subscript of biggest item found
        for (int i = 1; i < endMark; ++i)
        {
            if (!(p[i] < p[biggest]))  // Comparison is done this way for stability
                biggest = i;
        }

        // p[biggest] goes in position p[endMark-1]
        // So put it there
        std::swap(p[biggest], p[endMark-1]);
    }
}


// main
// Test function selectionSort (takes array)
int main()
{
    const int SIZE = 11;
    int arr[SIZE] = { 5, 3, 2, 8, 5, 9, 10, 4, 6, 1, -4 };
    selectionSort(arr, SIZE);
    for (int i = 0; i < SIZE; ++i)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}