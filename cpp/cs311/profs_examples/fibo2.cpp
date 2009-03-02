// fibo2.cpp
// Glenn G. Chappell
// 27 Sep 2006
//
// For CS 311
// Computing Fibonacci Numbers
// Version #2: Iterative

#include <iostream>
using std::cout;
using std::endl;


// fibo
// Given n, returns F(n) (the nth Fibonacci number).
// F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Pre:
//     n >= 0.
//     F(n) is a valid int value.
// Note: For 32-bit signed int's, preconditions hold for 0 <= n <= 46.
// Post:
//     Return value is F(n).
// Does not throw
int fibo(int n)
{
    int prevFibo = 1;
    int currFibo = 0;

    // Invariant:
    //     prevFibo == F(-1) == 1
    //     currFibo == F(0) == 0

    for (int k = 0; k < n; ++k)
    {
        // Loop invariant:
        //     prevFibo == F(k-1)
        //     currFibo == F(k)

        int sum = prevFibo + currFibo;
        prevFibo = currFibo;
        currFibo = sum;

        // Loop invariant:
        //     prevFibo == F(k)
        //     currFibo == F(k+1)
    }

    // Invariant:
    //     currFibo == F(n)

    return currFibo;
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
