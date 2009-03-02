// fibo4.cpp
// Glenn G. Chappell
// 29 Sep 2006
//
// For CS 311
// Computing Fibonacci Numbers
// Version #4: Recursive memoizing

#include <iostream>
using std::cout;
using std::endl;
#include <vector>  // for std::vector


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
//     fibos.size() >= n+1.
//     if fibos.size() was < n+1 before this function call,
//      then fibos.size() == max { 2, n+1 }.
// Invariants:
//     F 0 <= i < fibos.size(), fibos[i] == F(i).
//     fibos.size() != 1.
// Does not throw
int fibo(int n)
{
    // List of Fibonacci numbers; see "Invariants", above.
    static std::vector<int> fibos;

    // Have memo?
    if (fibos.size() > n)
        return fibos[n];

    // Base case
    if (n <= 1)
    {
        // Invariant: fibos.size() == 0
        fibos.push_back(0);
        fibos.push_back(1);
    }
    // Recursive case
    else
    {
        int returnVal =  fibo(n-2) + fibo(n-1);
        // Invariant: fibos.size() == n
        fibos.push_back(returnVal);
    }

    // Invariant: fibos[n] == F(n)

    // Return the value
    return fibos[n];
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
