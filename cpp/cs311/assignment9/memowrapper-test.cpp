// memowrapper-test.cpp
// Glenn G. Chappell
// 6 Dec 2006
//
// For CS 311
// Used in Assignment 9
// Test file for class MemoWrapper

#include "memowrapper.h"  // For class MemoWrapper
// Include above BEFORE system files, to make sure it works by itself
#include "memowrapper.h"  // Double inclusion test

#include <iostream>   // for std::cout, std::endl
#include <string>     // for std::string

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
    // Does not throw (No-Throw Guarantee)
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
    // Does not throw (No-Throw Guarantee)
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
    // Does not throw (No-Throw Guarantee)
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
    // Does not throw (No-Throw Guarantee)
    int numTests() const
    { return countTests; }

    // numPassed
    // Returns the number of tests that have passed since last reset
    // Pre: None.
    // Post:
    //     return == countPassed
    // Does not throw (No-Throw Guarantee)
    int numPassed() const
    { return countPasses; }

    // numFailed
    // Returns the number of tests that have not passed since last reset
    // Pre: None.
    // Post:
    //     return + countPasses == numTests
    // Does not throw (No-Throw Guarantee)
    int numFailed() const
    { return countTests - countPasses; }

    // allPassed
    // Returns true if all tests since last reset have passed
    // Pre: None.
    // Post:
    //     return == (countPasses == countTests)
    // Does not throw (No-Throw Guarantee)
    bool allPassed() const
    { return countPasses == countTests; }

// ***** Tester: data members *****
private:

    int countTests;   // Number of tests done since last reset
    int countPasses;  // Number of tests passed since last reset

};  // end class Tester

// ************************************************************************
// Classes for testing
// ************************************************************************

// class TestInType
// Input type for testing class MemoWrapper
// Invariants: None.
class TestInType {
};  // End class TestInType

bool operator<(const TestInType & a,
               const TestInType & b)
{ return false; }

// class TestOutType
// Output type for testing class MemoWrapper
// Invariants: None.
class TestOutType {
};  // End class TestOutType

TestOutType inOut(const TestInType & t)
{
    return TestOutType();
}

// ************************************************************************
// General callback functions
// ************************************************************************

int numCalls;

int firstChar(const std::string & s)
{
    ++numCalls;
    return int(s[0]);
}

std::string stringForm(const int & i)
{
    ++numCalls;
    std::string s;
    s.push_back(i);
    return s;
}

int plusOne(const int & n)
{
    ++numCalls;
    return n+1;
}

int minusOne(const int & n)
{
    return n-1;
}

// ************************************************************************
// Test Suite Functions
// ************************************************************************

// test_class_MemoWrapper_string_int
// Test suite for class MemoWrapper, taking string, returning int
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_MemoWrapper_string_int(Tester & t)
{
    std::cout << "Test Suite: class MemoWrapper - taking string, returning int" << std::endl;

    numCalls = 0;
    int saveNumCalls;

    {
        // Construction
        saveNumCalls = numCalls;
        MemoWrapper<std::string, int> m(firstChar);
        t.test(numCalls == saveNumCalls, "construction - no calls made");

        // Test 1: new parameters
        saveNumCalls = numCalls;
        t.test(m("a") == 'a', "value test #1a - correct value");
        t.test(numCalls == 1+saveNumCalls, "value test #1a - one call made");

        saveNumCalls = numCalls;
        t.test(m("b") == 'b', "value test #1b - correct value");
        t.test(numCalls == 1+saveNumCalls, "value test #1b - one call made");

        saveNumCalls = numCalls;
        t.test(m("c") == 'c', "value test #1c - correct value");
        t.test(numCalls == 1+saveNumCalls, "value test #1c - one call made");
        t.test(m("c") != 'd', "value test #1c - does not equal incorrect value");
        t.test(numCalls == 1+saveNumCalls, "value test #1c - one call made (again)");

        // Test 2: old parameters
        saveNumCalls = numCalls;
        t.test(m("a") == 'a', "value test #2a - correct value");
        t.test(numCalls == saveNumCalls, "value test #2a - no call made");

        saveNumCalls = numCalls;
        t.test(m("b") == 'b', "value test #2b - correct value");
        t.test(numCalls == saveNumCalls, "value test #2b - no call made");

        saveNumCalls = numCalls;
        t.test(m("c") == 'c', "value test #2c - correct value");
        t.test(numCalls == saveNumCalls, "value test #2c - no call made");

        // Test 3: new parameters
        saveNumCalls = numCalls;
        t.test(m("ax") == 'a', "value test #3a - correct value");
        t.test(numCalls == 1+saveNumCalls, "value test #3a - one call made");

        saveNumCalls = numCalls;
        t.test(m("ay") == 'a', "value test #3b - correct value");
        t.test(numCalls == 1+saveNumCalls, "value test #3b - one call made");

        saveNumCalls = numCalls;
        t.test(m("az") == 'a', "value test #3c - correct value");
        t.test(numCalls == 1+saveNumCalls, "value test #3c - one call made");

    // Destruction
        saveNumCalls = numCalls;
    }  // Call destructor
    t.test(numCalls == saveNumCalls, "Destruction - no call made");
}


// test_class_MemoWrapper_int_string
// Test suite for class MemoWrapper, taking int, returning string
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_MemoWrapper_int_string(Tester & t)
{
    std::cout << "Test Suite: class MemoWrapper - taking int, returning string" << std::endl;

    numCalls = 0;
    int saveNumCalls;

    MemoWrapper<int, std::string> m(stringForm);

    // Test 1: new parameters
    saveNumCalls = numCalls;
    t.test(m('a') == "a", "value test #1a - correct value");
    t.test(numCalls == 1+saveNumCalls, "value test #1a - one call made");

    saveNumCalls = numCalls;
    t.test(m('c') == "c", "value test #1b - correct value");
    t.test(numCalls == 1+saveNumCalls, "value test #1b - one call made");
    t.test(m('c') != "d", "value test #1b - does not equal incorrect value");
    t.test(numCalls == 1+saveNumCalls, "value test #1b - one call made (again)");

    // Test 2: old parameters
    saveNumCalls = numCalls;
    t.test(m('a') == "a", "value test #2a - correct value");
    t.test(numCalls == saveNumCalls, "value test #2a - no call made");

    saveNumCalls = numCalls;
    t.test(m('c') == "c", "value test #2b - correct value");
    t.test(numCalls == saveNumCalls, "value test #2b - no call made");

    // Test 3: new parameters
    saveNumCalls = numCalls;
    t.test(m('b') == "b", "value test #3 - correct value");
    t.test(numCalls == 1+saveNumCalls, "value test #3 - one call made");
}


// test_class_MemoWrapper_copy_ctor
// Test suite for class MemoWrapper, copy constructor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_MemoWrapper_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class MemoWrapper - copy constructor" << std::endl;

    numCalls = 0;
    int saveNumCalls;
    MemoWrapper<int, int> * p;

    {
        MemoWrapper<int, int> m(plusOne);

        int dummy;
        dummy = m(0);
        dummy = m(2);

        // Copy Construction
        // Dynamic, so we can destroy original
        p = new MemoWrapper<int, int>(m);

        try
        {
            saveNumCalls = numCalls;
            t.test((*p)(2) == 3, "copy constructed - value test - correct value");
            t.test(numCalls == saveNumCalls, "copy constructed - value test - no call made");
        }
        catch (...)
        {
            delete p;  // No memory leaks!
            throw;
        }

    // Destroy original
    }

    try
    {
        saveNumCalls = numCalls;
        t.test((*p)(0) == 1, "copy constructed - value test after dctor - correct value");
        t.test(numCalls == saveNumCalls, "copy constructed - value test after dctor - no call made");
    }
    catch (...)
    {
        delete p;  // No memory leaks!
        throw;
    }

    delete p;  // No memory leaks!
}


// test_class_MemoWrapper_copy_assn
// Test suite for class MemoWrapper, copy constructor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_MemoWrapper_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class MemoWrapper - copy assignment" << std::endl;

    numCalls = 0;
    int saveNumCalls;
    MemoWrapper<int, int> m2(minusOne);

    {
        MemoWrapper<int, int> m(plusOne);

        int dummy;
        dummy = m(0);
        dummy = m(2);

        // Copy assignment
        m2 = m;

        saveNumCalls = numCalls;
        t.test(m2(2) == 3, "copy assigned - value test - correct value");
        t.test(numCalls == saveNumCalls, "copy assigned - value test - no call made");

    // Destroy original
    }

    saveNumCalls = numCalls;
    t.test(m2(0) == 1, "copy assigned - value test after dctor - correct value");
    t.test(numCalls == saveNumCalls, "copy assigned - value test after dctor - no call made");
}


// test_class_MemoWrapper_minimal_types
// Test suite for class MemoWrapper using types with minimal functionality
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_MemoWrapper_minimal_types(Tester & t)
{
    std::cout << "Test Suite: class MemoWrapper - using types with minimal functionality" << std::endl;

    // Check compilation with types having minimal functionality (passes if code compiles)
    MemoWrapper<TestInType, TestOutType> m(inOut);
    TestOutType out = m(TestInType());
    t.test(true, "TestIntype & TestOutType");
}


// test_class_MemoWrapper
// Test suite for class MemoWrapper
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_MemoWrapper(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS MemoWrapper" << std::endl;
    test_class_MemoWrapper_string_int(t);
    test_class_MemoWrapper_int_string(t);
    test_class_MemoWrapper_copy_ctor(t);
    test_class_MemoWrapper_copy_assn(t);
    test_class_MemoWrapper_minimal_types(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs class MemoWrapper test suite, prints results to cout.
int main()
{
    Tester t;
    test_class_MemoWrapper(t);

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

