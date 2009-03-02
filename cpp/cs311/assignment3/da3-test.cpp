// da3-test.cpp
// Glenn G. Chappell
// 25 Sep 2006
//
// For CS 311
// Used in Assignment 3
// Test file for functions from Exercise A

#include "da3.h"  // For functions from Exercise A
// Include above BEFORE system files, to make sure it works by itself
#include "da3.h"  // Double inclusion test

#include <iostream>
using std::cout;
using std::endl;
#include <string>     // for std::string
#include <stdexcept>  // for std::exception, std::runtime_error
#include <sstream>    // for std::ostringstream
#include <vector>     // for std::vector
#include <list>       // for std::list
#include <algorithm>  // for std::equal
#include <iterator>   // for std::advance
#include <cmath>      // for std::fabs
#include <deque>      // for std::deque

// ************************************************************************
// Testing class
// ************************************************************************

// class Tester
// For extremely simple unit testing.
// Keeps track of number of tests and number of passes.
// Use test (with success/failure parameter) to do a test.
// Get results with numTests, numPassed, numFailed, allPassed.
// Restart testing with reset.
// Invariants:
//     countTests == number of tests (calls to test) since last reset.
//     countPasses == number of times function test called with true param
//      since last reset.
//     0 <= countPasses <= countTests.
class Tester {

// ***** Tester: ctors, dctor, op= *****
public:

    // Default ctor
    // Sets countTests, countPasses to zero
    // Pre: None.
    // Post:
    //     numTests == 0, countPasses == 0
    Tester()
        :countTests(0),
         countPasses(0)
    {}

    // Compiler-generated copy ctor, op=, dctor are used

// ***** Tester: general public functions *****
public:

    // test
    // Handles single test, param indicates pass/fail
    // Pre: None.
    // Post:
    //     countTests incremented
    //     countPasses incremented if (success)
    //     Message indicating test name (if given)
    //      and pass/fail printed to cout
    void test(bool success,
              const std::string & testName = "")
    {
        ++countTests;
        if (success) ++countPasses;

        std::cout << "    ";
        if (testName != "")
        {
            std::cout << "Test: "
                      << testName
                      << " - ";
        }
        std::cout << (success ? "passed" : "********** FAILED **********")
                  << std::endl;
    }

    // reset
    // Resets *this to default constructed state
    // Pre: None.
    // Post:
    //     countTests == 0, countPasses == 0
    void reset()
    {
        countTests = 0;
        countPasses = 0;
    }

    // numTests
    // Returns the number of tests that have been done since last reset 
    // Pre: None.
    // Post:
    //     return == countTests
    int numTests() const
    { return countTests; }

    // numPassed
    // Returns the number of tests that have passed since last reset
    // Pre: None.
    // Post:
    //     return == countPassed
    int numPassed() const
    { return countPasses; }

    // numFailed
    // Returns the number of tests that have not passed since last reset
    // Pre: None.
    // Post:
    //     return + countPasses == numTests
    int numFailed() const
    { return countTests - countPasses; }

    // allPassed
    // Returns true if all tests since last reset have passed
    // Pre: None.
    // Post:
    //     return == (countPasses == countTests)
    bool allPassed() const
    { return countPasses == countTests; }

// ***** Tester: data members *****
private:

    int countTests;   // Number of tests done since last reset
    int countPasses;  // Number of tests passed since last reset

};  // end class Tester

// ************************************************************************
// Callback functions
// ************************************************************************

// thisThrows
// Throws a std::runtime_error. For passing to function doesThisThrow.
// Pre: None.
// Post: None.
// Will throw std::runtime_error.
void thisThrows()
{
    throw std::runtime_error("Hi!");
}

// thisThrowsOddly
// Throws an int. For passing to function doesThisThrow.
// Pre: None.
// Post: None.
// Will throw int.
void thisThrowsOddly()
{
    throw 1;
}

// thisDoesNotThrow
// Does nothing. For passing to function doesThisThrow.
// Pre: None.
// Post: None.
// Does not throw.
void thisDoesNotThrow()
{}

// ************************************************************************
// Function object class
// ************************************************************************

// class FuncObj
// Class for do-nothing function objects.
// Do "FuncObj x;", and then we can do "x();".
// The operator() returns nothing and does not throw.
// Invariants: None.
class FuncObj {

// ***** FuncObj: ctors, dctor, op= *****
public:

    // Compiler-generated default ctor, copy ctor, op=, dctor are used

// ***** FuncObj: public operators *****
public:

    // operator()
    // Makes an object of this class callable like a function.
    // Pre: None.
    // Post: None.
    // Does not throw.
    void operator()() const
    {}

};  // end class FuncObj

// ************************************************************************
// Test Suite Functions
// ************************************************************************

// test_function_doesThisThrow
// Test suite for function doesThisThrow
//  ctor, dctor.
// Pre: None.
// Post:
//     Global allpassed is false if any tests failed;
//      it is unchanged otherwise.
//     Messages have been printed to cout.
void test_function_doesThisThrow(Tester & t)
{
    cout << "Test Suite: function doesThisThrow" << endl;

    // Function throws standard exception class
    t.test(doesThisThrow(thisThrows), "Throwing function");

    // Function throws int
    t.test(doesThisThrow(thisThrowsOddly), "Throwing function (non-std exception type)");

    // Function does not throw
    t.test(!doesThisThrow(thisDoesNotThrow), "Non-throwing function");

    // Function object - does not throw
    t.test(!doesThisThrow(FuncObj()), "Function object");
}


// test_function_printRev
// Test suite for function printRev
//  ctor, dctor.
// Pre: None.
// Post:
//     Global allpassed is false if any tests failed;
//      it is unchanged otherwise.
//     Messages have been printed to cout.
void test_function_printRev(Tester & t)
{
    cout << "Test Suite: function printRev" << endl;

    // Empty (char *)
    std::ostringstream os1;
    printRev(os1, "");
    t.test(os1.str() == "", "Empty (char *)");

    // Empty string object
    std::ostringstream os2;
    printRev(os2, std::string(""));
    t.test(os2.str() == "", "Empty string object");

    // 1 char
    std::ostringstream os3;
    printRev(os3, "x");
    t.test(os3.str() == "x", "One character");

    // 2 chars
    std::ostringstream os4;
    printRev(os4, "aB");
    t.test(os4.str() == "Ba", "Two characters");

    // Longer string
    std::ostringstream os5;
    printRev(os5, "This is a test!");
    t.test(os5.str() == "!tset a si sihT", "Longer string");
}


// test_function_divideAll
// Test suite for function divideAll
//  ctor, dctor.
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_function_divideAll(Tester & t)
{
    cout << "Test Suite: function divideAll" << endl;

    const int DATASIZE = 5;
    int data[DATASIZE] = { 6, 12, 18, 24, 30 };
    // Make copies of data
    const std::vector<int> dataCheck(data, data+DATASIZE);
    std::list<int> dataList(data, data+DATASIZE);
    // Modified data
    const int dataMod[DATASIZE] = { 6, 4, 6, 8, 30 };


    // Throwing behavior
    bool didThrow = false;
    bool threwNonStdType = false;
    try
    {
        divideAll(data, data+DATASIZE, 0);
    }
    catch (std::exception & e)  // Catch std exception object
    {
        didThrow = true;
        t.test(std::string("") != e.what(), "`what' member of exception object is non-empty");
    }
    catch (...)  // Catch non-std exection object
    {
        didThrow = true;
        threwNonStdType = true;
    }
    t.test(didThrow, "Exception thrown on division by zero");
    t.test(!threwNonStdType, "Exception object of standard class or a derived class");
    t.test(std::equal(data, data+DATASIZE, dataCheck.begin()), "Data unmodified when exception thrown");

    // Empty range
    divideAll(data+2, data+2, 4);
    t.test(std::equal(data, data+DATASIZE, dataCheck.begin()), "Test with empty range");

    // Try array
    divideAll(data+1, data+4, 3);
    t.test(std::equal(data, data+DATASIZE, dataMod), "Test modification of array data");

    // Try std::list
    std::list<int>::iterator it1 = dataList.begin();
    std::advance(it1, 1);
    std::list<int>::iterator it2 = dataList.begin();
    std::advance(it2, 4);
    divideAll(it1, it2, 3);
    t.test(std::equal(dataList.begin(), dataList.end(), dataMod), "Test modification of std::list");

    // Try non-int data
    const int DOUBLEDATASIZE = 3;
    const double TOLERANCE = 0.00001;  // Tolerance for near equality
    double doubleData[DOUBLEDATASIZE] = { 0.11, 0.22, 0.33 };
    divideAll(doubleData+1, doubleData+2, 0.2);
    t.test(std::fabs(doubleData[0] - 0.11) < TOLERANCE, "Test modification of non-int data #1");
    t.test(std::fabs(doubleData[1] - 1.1)  < TOLERANCE, "Test modification of non-int data #2");
    t.test(std::fabs(doubleData[2] - 0.33) < TOLERANCE, "Test modification of non-int data #3");
}


// test_function_sortDescendingInt
// Test suite for function sortDescendingInt
//  ctor, dctor.
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_function_sortDescendingInt(Tester & t)
{
    cout << "Test Suite: function sortDescendingInt" << endl;

    const int DATASIZE = 20;
    int data[DATASIZE] = { 3, 6, 19, -2, 8, 6, 7, 1, 141, -2, -200, 4, 6, 6, 11, -5, 32, 2, 7, 0 };
    // Make copies of data
    const std::vector<int> dataCheck(data, data+DATASIZE);
    std::deque<int> data2(data, data+DATASIZE);
    // Sorted data (all but first, last)
    const int dataSorted[DATASIZE] = { 3, 141, 32, 19, 11, 8, 7, 7, 6, 6, 6, 6, 4, 2, 1, -2, -2, -5, -200, 0 };


    // Empty range
    sortDescendingInt(data+3, data+3);
    t.test(std::equal(data, data+DATASIZE, dataCheck.begin()), "Array: empty range");

    // One item
    sortDescendingInt(data+3, data+4);
    t.test(std::equal(data, data+DATASIZE, dataCheck.begin()), "Array: one item");

    // Sort array
    sortDescendingInt(data+1, data+(DATASIZE-1));
    t.test(std::equal(data, data+DATASIZE, dataSorted), "Array: longer");

    // Sort other random-access container
    sortDescendingInt(data2.begin()+1, data2.end()-1);
    t.test(std::equal(data2.begin(), data2.end(), dataSorted), "Other random-access container");
}


// test_assignment_3_exercise_A
// Test suite for functions from Assignment 3, Exercise A
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_assignment_3_exercise_A(Tester & t)
{
    // Do all the test suites
    cout << "TEST SUITES FOR ASSIGNMENT 3, EXERCISE A" << endl;
    test_function_doesThisThrow(t);
    test_function_printRev(t);
    test_function_divideAll(t);
    test_function_sortDescendingInt(t);
}

// ************************************************************************
// Main program
// ************************************************************************

// main
// Runs Assignment 3 test suite, prints results to cout.
int main()
{
    Tester t;
    test_assignment_3_exercise_A(t);

    std::cout << std::endl;
    if (t.allPassed())
    {
        std::cout << "All tests successful" 
                  << std::endl;
    }
    else
    {
        std::cout << "Tests ********** UNSUCCESSFUL **********"
                  << std::endl;
    }
    std::cout << std::endl;
}
