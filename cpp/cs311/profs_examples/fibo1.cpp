// fibo1.cpp
// Glenn G. Chappell
// 27 Sep 2006
//
// For CS 311
// Computing Fibonacci Numbers
// Version #1: Recursive

#include <iostream>
using std::cout;
using std::endl;


// fibo
// Given n, returns F(n) (the nth Fibonacci number).
// F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Recursive.
// Pre:
//     n >= 0.
//     F(n) is a valid int value.
// Note: For 32-bit signed int's, preconditions hold for 0 <= n <= 46.
// Post:
//     Return value is F(n).
// Does not throw
int fibo(int n)
{
    // Base case
    if (n <= 1)
        return n;

    // Recursive case
    return fibo(n-2) + fibo(n-1);
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
