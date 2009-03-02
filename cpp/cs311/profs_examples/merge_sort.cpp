// merge_sort.cpp
// Glenn G. Chappell
// 13 Oct 2005
//
// For CS 311
// Merge Sort Using Forward Iterators

#include <iostream>
using std::cout;
using std::endl;

#include <vector>     // For std::vector
#include <iterator>   // For std::distance, std::advance, std::iterator_traits
#include <cstdlib>    // For std::size_t
#include <algorithm>  // For std::copy


// stableMerge
// Merge two halves of a sequence, each sorted,
//  into a single sorted sequence in the same location.
//  Merge is done in a stable manner.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, middle) and [middle, last) are valid ranges,
//      each sorted by <.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename FDIter>
void stableMerge(FDIter first, FDIter middle, FDIter last)
{
    typedef std::iterator_traits<FDIter>::value_type ValueType;
        // Data type that FDIter points to
    typedef std::vector<ValueType> BufferType;
        // Type of buffer to hold temporary copy of data

    BufferType buffer(std::distance(first, last));
                          // Buffer to hold temporary copy of data
    FDIter in1 = first;   // Current read location in 1st half
    FDIter in2 = middle;  // Current read location in 2nd half
    BufferType::iterator out = buffer.begin();
                          // Current write location in buffer

    // Merge two sorted lists into a single list in buff.
    while (in1 != middle && in2 != last)
    {
        if (*in2 < *in1)  // Must do comparison this way, to be stable.
            *out++ = *in2++;
        else
            *out++ = *in1++;
    }

    // Copy remainder of original sequence to buffer.
    // Only one of the following two copy calls will do anything.
    std::copy(in1, middle, out);
    std::copy(in2, last, out);

    // Copy buffer contents back to original sequence location.
    std::copy(buffer.begin(), buffer.end(), first);
}


// mergeSort
// Sorts a sequence, using Merge Sort.
// Recursive.
// Requirements on Types:
//     FDIter is a forward iterator type.
//     operator< is a total order on the value type of FDIter.
// Pre:
//     [first, last) is a valid range.
// Post:
//     [first, last) contains the same items as it did initially,
//      but now sorted by < (in a stable manner).
template <typename FDIter>
void mergeSort(FDIter first, FDIter last)
{
    std::size_t size = std::distance(first, last);

    // BASE CASE
    if (size <= 1)
        return;

    // RECURSIVE CASE
    FDIter middle = first;
    std::advance(middle, size/2);  // middle is iterator to middle of sequence

    // Recursively sort the two lists
    mergeSort(first, middle);
    mergeSort(middle, last);
    // And merge them
    stableMerge(first, middle, last);
}


// main
// Test function mergeSort, iterator version
int main()
{
   const int SIZE = 11;
   int arr[SIZE] = { 5, 3, 2, 8, 5, 9, 10, 4, 6, 1, -4};
   std::vector<int> v(arr, arr+SIZE);
   mergeSort(v.begin(), v.end());
   // I sort a std::vector, rather than an array, because
   //  std::iterator_traits is broken on MS-Vis C++ (even version 7.0).
   // On a standard-conforming compiler, the following should work:
   //    mergeSort(arr, arr+SIZE);

   for (int i = 0; i < SIZE; ++i)
      cout << v[i] << " ";
   cout << endl;

   return 0;
}