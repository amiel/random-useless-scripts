// fibo6.cpp
// Glenn G. Chappell
// 10 Nov 2006
//
// For CS 311
// Computing Fibonacci Numbers
// Version #6: Recursion Eliminated
//
// This program is based on fibo1.cpp.
// Recursion has been eliminated using
//  the technique described in class.

#include <iostream>
using std::cout;
using std::endl;
#include <stack>  // for std::stack


/*
Original function fibo, from fibo1.cpp:

int fibo(int n)
{
    // Base case
    if (n <= 1)
        return n;

    // Recursive case
    return fibo(n-2) + fibo(n-1);
}

Modified version used as the basis of this code:

int fibo(int n)
{
    int v1, v2;

    // Base case
    if (n <= 1)
        return n;

    // Recursive call #1
    v1 = fibo(n-2);

    // Recursive call #2
    v2 = fibo(n-1);

    // Return the result
    return v1 + v2;
}
*/


// struct FiboStackFrame
// "Stack frame" - holds local vars for function fibo.
// In a structure so that they can be saved on a stack.
struct FiboStackFrame {
int n;            // parameter
int v1;           // result of recursive call #1
int v2;           // result of recursive call #2
int returnValue;  // value to return
int returnAddr;   // return address:
                    //     0: outside world (return from function)
                    //     1: recursive call #1 (return to label1)
                    //     2: recursive call #2 (return to label2)
};


// fibo
// Given n, returns F(n) (the nth Fibonacci number).
// F(0) = 0. F(1) = 1. For n >= 2, F(n) = F(n-2) + F(n-1).
// Pre:
//     n >= 0.
//     F(n) is a valid int value.
// Note: For 32-bit signed int's, preconditions hold for 0 <= n <= 46.
// Post:
//     Return value is F(n).
// No-Throw Guarantee
int fibo(int n)
{
    // *************************************
    // LOCAL VARIABLES
    // *************************************
    int tmp;  // Temp value - holds an int during stack op's
    std::stack<FiboStackFrame> s;
              // Stack, used to eliminate recursion
              // Top of stack holds current local variables
              //  and place for return value

    // *************************************
    // Set up stack frame.
    //
    // ORIGINAL CODE:
    // int fibo(int n)
    // {
    //     int v1, v2;
    // *************************************
    s.push(FiboStackFrame());  // make new stack frame
    s.top().n = n;             // set parameter
    s.top().returnAddr = 0;    // set return address (called by outside world)

    // *************************************
    // BEGIN LOOP
    // while (true) loop used for recursion
    // elimination.
    // *************************************
    while (true)
    {
        // *************************************
        // ORIGINAL CODE:
        // // Base case
        // if (n <= 1)
        //     return n;
        // *************************************
        if (s.top().n <= 1)
        {
            // Do "return n;"
            s.top().returnValue = s.top().n;

            if (s.top().returnAddr == 0)  // called by outside world
            {
                tmp = s.top().returnValue;
                s.pop();
                return tmp;
            }
            if (s.top().returnAddr == 1)  // called by recursive call #1
            {
                goto label1;
            }
            if (s.top().returnAddr == 2)  // called by recursive call #2
            {
                goto label2;
            }
        }

        // *************************************
        // ORIGINAL CODE:
        // // Recursive call #1
        // v1 = fibo(n-2);
        // *************************************
        tmp = s.top().n - 2;
        s.push(FiboStackFrame());  // make new stack frame
        s.top().n = tmp;           // set parameter
        s.top().returnAddr = 1;    // set return address (recursive call #1)
        continue;                  // Do "recursive call"
label1:                            // Place to return to
        tmp = s.top().returnValue;
        s.pop();
        s.top().v1 = tmp;          // put returned value in v1

        // *************************************
        // ORIGINAL CODE:
        // // Recursive call #2
        // v2 = fibo(n-1);
        // *************************************
        tmp = s.top().n - 1;
        s.push(FiboStackFrame());  // make new stack frame
        s.top().n = tmp;           // set parameter
        s.top().returnAddr = 2;    // set return address (recursive call #2)
        continue;                  // Do "recursive call"
label2:                            // Place to return to
        tmp = s.top().returnValue;
        s.pop();
        s.top().v2 = tmp;          // put returned value in v2

        // *************************************
        // ORIGINAL CODE:
        // // Return the result
        // return v1 + v2;
        // *************************************
        s.top().returnValue = s.top().v1 + s.top().v2;

        if (s.top().returnAddr == 0)  // called by outside world
        {
            tmp = s.top().returnValue;
            s.pop();
            return tmp;
        }
        if (s.top().returnAddr == 1)  // called by recursive call #1
        {
            goto label1;
        }
        if (s.top().returnAddr == 2)  // called by recursive call #2
        {
            goto label2;
        }

    // *************************************
    // END LOOP
    // while (true) loop used for recursion
    // elimination.
    // *************************************
    }
}


// main
// From fibo1.cpp
int main()
{
    cout << "Fibonacci Numbers" << endl;
    cout << endl;
    for (int i = 0; i < 50; ++i)
    {
        cout << i << ": " << fibo(i) << endl;
    }
}
