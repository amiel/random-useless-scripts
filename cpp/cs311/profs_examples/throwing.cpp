// throwing.cpp
// Glenn G. Chappell
// 20 Sept 2006
//
// For CS 311
// Demonstration of throwing & catching an exception

// (1) Run the program, and see its output.
// (2) Uncomment the throw statement in function foo.
//     Run the program, and compare the output.
// (3) Try throwing an exception in one of the Bar member
//     functions. How does this interact with the throw
//     (or lack thereof) in function foo?

// NOTE: This code is only for demonstration purposes.
//  Remember that, normally, you will not write
//  BOTH the "throw" and the "catch".






#include <iostream>
using std::cout;
using std::endl;
#include <stdexcept>  // for std::range_error


// class Bar
// Empty class that prints messages
// Invariants: None.
class Bar {
public:
    // default ctor
    // Pre: None.
    // Post:
    //     Message printed.
    Bar()
    { cout << "Bar default ctor" << endl; }

    // Dctor
    // Pre: None.
    // Post:
    //     Message printed.
    ~Bar()
    { cout << "Bar dctor" << endl; }
};  // End class Bar


// foo
// A function that may throw
// Pre: None.
// Post:
//     Messages printed.
// May throw std::range_error
void foo()
{
    Bar x;
    cout << "foo 1" << endl;
    throw std::range_error("This is a range error! Wow!");
    cout << "foo 2" << endl;
}


// main
int main()
{
    cout << "main 1" << endl;

    try
    {
        cout << "main 2" << endl;
        foo();
        cout << "main 3" << endl;
    }
    catch (std::range_error & e)
    {
        cout << "Caught exception. Message = " << e.what() << endl;
    }

    cout << "main 4" << endl;
}
