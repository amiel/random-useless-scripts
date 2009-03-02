// rpn.cpp
// Glenn G. Chappell
// 10 Nov 2006
//
// For CS 311
// Reverse-Polish Notation expression evaluation
// Example application of a stack


#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <sstream>
using std::istringstream;
#include <string>
using std::string;
#include <stack>
using std::stack;


// toInt
// Converts a string to an int
// Pre: None.
// Post:
//    Return value is int version of s,
//     as determined by operator>>(istream &, int &).
// No-Throw Guarantee
int toInt(const string & s)
{
    istringstream istr(s);
    int n;
    istr >> n;
    return n;
}


// rpn
// Reverse-Polish Notation computation.
// Given a string and a stack, interpret the string as a command
// and use it to operate on the stack.
// Command type is determined by its first character.
//     0-9: positive int to push on stack.
//      (Negative values cannot be entered.)
//     +, -, *, /: binary operator. ("/" is integer division.)
//      Operands are taken from top two items on stack.
//      Result is left in top item on stack.
//
// Pre:
//     None.
// Post:
//     s (Stack) was transformed appropriately, if possible.
//     If s.size() was too small to complete operation,
//      then s is unchanged.
// May throw (unknown exception) on stack overflow/out of memory.
// Basic Guarantee.
void rpn(const std::string & token,
         std::stack<int> & s)
{
    int a, b;

    switch (token[0])
    {
    case '0':  // '0' - '9': push number
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
        s.push(toInt(token));
        break;
    case '+':  // '+': add
        if (s.size() < 2) return;
        b = s.top();
        s.pop();
        a = s.top();
        s.pop();
        s.push(a + b);
        break;
    case '-':  // '-': subtract
        if (s.size() < 2) return;
        b = s.top();
        s.pop();
        a = s.top();
        s.pop();
        s.push(a - b);
        break;
    case '*':  // '*': multiply
        if (s.size() < 2) return;
        b = s.top();
        s.pop();
        a = s.top();
        s.pop();
        s.push(a * b);
        break;
    case '/':  // '/': divide (integer)
        if (s.size() < 2) return;
        b = s.top();
        s.pop();
        a = s.top();
        s.pop();
        s.push(a / b);
        break;
    default:   // Unknown symbol: do nothing
        break;
    }
}


int main()
{
    std::stack<int> s;
    while (true)
    {
        // Input space-delimited command ("token")
        cout << "Command: ";
        std::string token;
        if (cin.eof()) exit(0);
        cin >> token;
        while (!cin)
        {
            if (cin.eof()) exit(0);
            cin.ignore();
            cin.clear();
            cin >> token;
        }
        cout << endl;

        // Do RPN processing
        rpn(token, s);

        // Print top of stack
        if (s.empty())
        {
            cout << "<Empty stack>" << endl;
        }
        else
        {
            cout << "Top: " << s.top() << endl;
        }
        cout << endl;
    }
    return 0;
}