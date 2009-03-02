// domino-test.cpp
// Glenn G. Chappell
// 30 Sep 2006
//
// For CS 311
// Used in Assignment 4
// Test file for function domino

#include "domino.h"  // For function domino
// Include above BEFORE system files, to make sure it works by itself
#include "domino.h"  // Double inclusion test

#include <iostream>  // for std::cout, std::endl
#include <string>    // for std::string
#include <sstream>   // for std::ostringstream

// ************************************************************************
// Global variables
// ************************************************************************

// Test data for domino function
// Format of each row: m, n, domino(m, n)
// Row -1, -1, -1 marks end of data
const int domino_test_data[][3] = {
    {  1,  1,    0 },  // all pairs with m, n = 1 .. 4
    {  1,  2,    1 },
    {  1,  3,    0 },
    {  1,  4,    1 },
    {  2,  1,    1 },
    {  2,  2,    2 },
    {  2,  3,    3 },
    {  2,  4,    5 },
    {  3,  1,    0 },
    {  3,  2,    3 },
    {  3,  3,    0 },
    {  3,  4,   11 },
    {  4,  1,    1 },
    {  4,  2,    5 },
    {  4,  3,   11 },
    {  4,  4,   36 },
    {  6,  6, 6728 },  // a few larger values
    {  2, 16, 1597 },
    { 12,  3, 2131 },
    { -1, -1,   -1 }   // end mark
};

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
// Test Suite Functions
// ************************************************************************

// test_function_domino_values
// Test suite for function domino, function values
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_function_domino_values(Tester & t)
{
    std::cout << "Test Suite: function domino - values" << std::endl;

    for (int i = 0;
         domino_test_data[i][0] >= 0;
         ++i)
    {
        int m = domino_test_data[i][0];
        int n = domino_test_data[i][1];
        int desired_result = domino_test_data[i][2];
        int actual_result = domino(m, n);
        std::ostringstream osmsg;
        osmsg << "domino value test - domino("
              << m << ", " << n << ") == "
              << desired_result;
        t.test(actual_result == desired_result, osmsg.str());
    }
}

// test_function_domino
// Test suite for function domino
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_function_domino(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR FUNCTION domino" << std::endl;
    test_function_domino_values(t);
}

// ************************************************************************
// Main program
// ************************************************************************

// main
// Runs function domino test suite, prints results to cout.
int main()
{
    Tester t;
    test_function_domino(t);

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

