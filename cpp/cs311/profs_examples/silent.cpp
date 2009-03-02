// silent.cpp
// Glenn G. Chappell
// 8 Sep 2006
//
// For CS 311
// Demo of silently written & called functions

// NOTE: THIS IS A DELIBERATELY BAD EXAMPLE.
// DO NOT IMITATE IT!

#include <iostream>
using std::cout;
using std::endl;


// class Cat
// Default ctor & dctor print messages
// Invariants: None.
class Cat {

// ***** Cat: ctor, dctor *****
public:
    // Default ctor
    // Prints a message
    // Pre: None.
    // Post: Message printed to cout.
    Cat()
    {
        cout << "Cat default ctor" << endl;
    }

    // Dctor
    // Prints a message
    // Pre: None.
    // Post: Message printed to cout.
    ~Cat()
    {
        cout << "Cat dctor" << endl;
    }
};  // End class Cat

// class Dog
// What member functions does this have?
// Invariants: None.
class Dog {

// ***** Dog: Data members *****
private:
    int a;
    double b;
    Cat c;
};  // End class Dog


// Global variables
Dog array[5];

// main
// Do-almost-nothing program - prints a message.
int main()
{
    cout << "Function main" << endl;
}
