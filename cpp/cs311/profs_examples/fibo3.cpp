// fibo3.cpp
// Glenn G. Chappell
// 29 Sep 2006
//
// For CS 311
// Computing Fibonacci Numbers
// Version #3: Recursive (workhorse & wrapper)

#include <iostream>
using std::cout;
using std::endl;
#include <utility>  // for std::pair


// Type: pair of ints
typedef std::pair<int, int> ipair;


// fibo_recurse
// Given n, returns F(n-1), F(n) (the nth Fibonacci number).
// F(-1) = 1. F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Recursive.
// Pre:
//     n >= 0.
//     F(n) is a valid int value.
// Note: For 32-bit signed int's, preconditions hold for 0 <= n <= 46.
// Post:
//     Return value is std::pair<int, int>(F(n-1), F(n)).
// Does not throw
ipair fibo_recurse(int n)
{

    // Base case
    if (n == 0)
        return ipair(1, 0);

    // Recursive case
    ipair oldPair = fibo_recurse(n-1);
    return ipair(oldPair.second, oldPair.first + oldPair.second);
}


// fibo
// Given n, returns F(n) (the nth Fibonacci number).
// F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Uses fibo_recurse.
// Pre:
//     n >= 0.
//     F(n) is a valid int value.
// Note: For 32-bit signed int's, preconditions hold for 0 <= n <= 46.
// Post:
//     Return value is F(n).
// Does not throw
int fibo(int n)
{
    return fibo_recurse(n).second;
}



int main()
{
    cout << "Fibonacci Numbers" << endl;
    cout << endl;
    for (int i = 0; i < 50; ++i)
    {
        cout << i << ": " << fibo(i) << endl;
    }
}
