// radix_sort.cpp
// Glenn G. Chappell
// 18 Oct 2006
//
// For CS 311
// Radix Sort Using Forward Iterators

#include <iostream>
using std::cout;
using std::endl;

#include <vector>  // for std::vector;


// radixSort
// Sorts a sequence of 5-digit nonnegative int's, using Radix Sort.
// Requirements on Types:
//     FDIter must be a forward iterator type.
//     FDIter::value_type must be int.
// Pre:
//     [first, last) is a valid range.
//     Items in [first, last) are all in [0, 99999]
//      (5-digit nonnegative int's)
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename FDIter>
void radixSort(FDIter first, FDIter last)
{
   const int RADIX_SORT_NUM_PLACES = 5;  // Number of Radix Sort passes
   int powerOfTen = 1;                   // 10 ^ place

   for (int place = 0; place < RADIX_SORT_NUM_PLACES; ++place)
   {
       std::vector<std::vector<int> > buckets(10);

       // place each item in the appropriate bucket (stable!)
       for (FDIter it = first; it != last; ++it)
       {
           buckets[((*it)/powerOfTen) % 10].push_back(*it);
       }

       // Copy each bucket back to original list, one after the other
       FDIter copyBack = first;
       for (int i = 0; i < 10; ++i)
       {
           copyBack =
               std::copy(buckets[i].begin(), buckets[i].end(), copyBack);
       }

       // Move to next power of 10
       powerOfTen *= 10;
   }
}


// main
// Test function radixSort (takes iterators)
int main()
{
    const int SIZE = 11;
    //int arr[SIZE] = { 5, 3, 2, 8, 5, 9, 10, 4, 6, 1, -4};
    // Negative values not allowed
    int arr[SIZE] = { 35, 1, 98, 434, 280, 281, 271, 180, 0, 50, 50 };
    radixSort(arr, arr+SIZE);
    for (int i = 0; i < SIZE; ++i)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
