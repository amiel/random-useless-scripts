// fibo5.cpp
// Glenn G. Chappell
// 29 Sep 2006
//
// For CS 311
// Computing Fibonacci Numbers
// Version #5: Formula

#include <iostream>
using std::cout;
using std::endl;
#include <cmath>  // for std::sqrt, std::pow


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
    const double sqrt5 = std::sqrt(5);
    const double phi = (1. + sqrt5) / 2.;      // "Golden ratio"

    double nearly = std::pow(phi, n) / sqrt5;  // phi^n/sqrt(5)

    // Our Fibonacci number is the nearest integer
    return int(nearly + 0.5);
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
