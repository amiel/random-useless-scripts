// usesetalg.cpp
// Glenn G. Chappell
// 1 Dec 2006
// 
// For CS 311
// Example using set algorithms
//  and "exotic" iterators

#include <iostream>
using std::cout;
using std::endl;
#include <set>        // for std::set
#include <algorithm>  // for std::set_intersection, std::copy
#include <iterator>   // for std::inserter, std::ostream_iterator


int main()
{
    // fiboSet is set of Fibonacci numbers,
    //  starting at 0, going at least to 10000.
    std::set<int> fiboSet;
    int f1 = 0;
    int f2 = 1;
    for (int i = 0; i < 40; ++i)
    {
        fiboSet.insert(f1);
        int f3 = f1 + f2;
        f1 = f2;
        f2 = f3;
    }

    // evenSet is set of even integers in [0, 10000).
    std::set<int> evenSet;
    for (int j = 0; 2*j < 10000; ++j)
    {
        evenSet.insert(2*j);
    }


    // resultSet is intersection of fiboSet and evenSet,
    //  that is, the set of all nonnegative even
    //  Fibonacci numbers less than 10000.
    std::set<int> resultSet;
    std::set_intersection(fiboSet.begin(), fiboSet.end(),
                          evenSet.begin(), evenSet.end(),
                          std::inserter(resultSet, resultSet.begin()));

    // Print the items in resultSet
    cout << "All even Fibonacci numbers less than 10000:" << endl;
    std::copy(resultSet.begin(), resultSet.end(),
              std::ostream_iterator<int>(cout, " "));
    cout << endl;
}
