// insertion_sort.cpp
// Glenn G. Chappell
// 11 Oct 2006
//
// For CS 311
// Insertion Sort on an Array

#include <iostream>
using std::cout;
using std::endl;
#include <algorithm>  // for std::rotate


// insertionSort
// Do Insertion Sort on a given array.
// Requirements on Types:
//     operator< must be a total order on T.
//     T must have a copy ctor and copy assignment.
// Pre:
//     p points to an array of at least n items of type T
// Post:
//     p[0 .. n-1] contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename T>
void insertionSort(T p[], int n)
{
    // Iterate through the items, inserting item i in the proper
    //  place among items 0 .. i-1.
    for (int i = 1; i < n; ++i)  // i is item to insert into earlier items
    {
        // Loop invariant: p[0 .. i-1] are sorted by < (in a stable manner).

        // Find the proper location for p[i], using backwards Sequential Search 
        for (int k = i-1; k >= 0; --k)
        {
            if (!(p[i] < p[k]))  // Do comparison this way, so we are stable
                break;
        }
        // Now p[i] goes in location k+1.
        
        // Rotate other items up and put p[i] in the correct location.
        std::rotate(&p[k+1], &p[i], &p[i+1]);
        // The above line replaces the following code:
        //  T saveItem = p[i];
        //  for (int m = i-1; m > k; --m)
        //      p[m+1] = p[m];
        //  p[k+1] = saveItem;
    }
}


// main
// Test function insertionSort (takes array)
int main()
{
    const int SIZE = 11;
    int arr[SIZE] = { 5, 3, 2, 8, 5, 9, 10, 4, 6, 1, -4 };
    insertionSort(arr, SIZE);
    for (int i = 0; i < SIZE; ++i)
        cout << arr[i] << " ";
    cout << endl;
    return 0;
}