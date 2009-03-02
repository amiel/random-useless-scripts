// heapalg-test.cpp
// Glenn G. Chappell
// 28 Nov 2006
//
// For CS 311
// Used in Assignment 8
// Test file for Heap algorithms

#include "heapalg.h"  // For class DList
// Include above BEFORE system files, to make sure it works by itself
#include "heapalg.h"  // Double inclusion test

#include <iostream>   // for std::cout, std::endl
#include <string>     // for std::string

#include <deque>      // for std::deque
#include <algorithm>  // for std::equal, std::reverse

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
// Class for type checking
// ************************************************************************

// class MustBe2
// This class exists in order to have static member function checkType.
// Objects of type MustBe2<T> cannot be created.
// Usage:
//     MustBe2<MyType>::checkType(x)
//     returns true if x is of type MyType, false otherwise.
//     Const/non-const issues are not dealt with.
// Invariants: None.
// Requirements on Types:
//     None.
template<typename T>
class MustBe2 {

public:

    // checkType
    // These two functions simulate a single function that takes a
    // single parameter of any type, and returns true if the parameter
    // is of type T, false otherwise.

    // checkType (type T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool checkType(const T & dummy)
    { return true; }

    // checkType (other type)
    // Pre: None.
    // Post:
    //     Return is false.
    // Does not throw (No-Throw Guarantee)
    template<typename Other>
    static bool checkType(const Other & dummy)
    { return false; }

private:

    // Uncopyable class. Do not define copy ctor, copy assn.
    MustBe2(const MustBe2 &);
    MustBe2<T> & operator=(const MustBe2 &);

    // Compiler-generated dctor is used (but irrelevant).

};  // End class MustBe

// ************************************************************************
// Class for type requirements checking
// ************************************************************************

// class OnlyLessThan
// For objects with limited operator availability.
// Has only default ctor, big 3, and operator< (always returns false).
// In particular, does not have operators ==, !=, >, >=.
// Invariants: None.
class OnlyLessThan {

    // Compiler-generated default ctor, copy ctor, copy =, dctor used

};  // End class OnlyLessThan

// operator< (OnlyLessThan)
// Fake operator< for OnlyLessThan class
// Returns false - which is legal, if all objects of type OnlyLessThan
// represent the same numeric value.
// Pre: None.
// Post:
//     Return is false.
// Does not throw (No-Throw Guarantee)
bool operator<(const OnlyLessThan & a,
               const OnlyLessThan & b)
{ return false; }

// ************************************************************************
// Test Suite Functions
// ************************************************************************

// test_heapalg_types
// Test suite for Heap algorithms, types
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_heapalg_types(Tester & t)
{
    std::cout << "Test Suite: Heap algorithms - types and type requirements" << std::endl;

    bool result;  // For return value of heapTest

    // Check return type of heapTest
    int arr1[1] = { 1 };
    t.test(MustBe2<bool>::checkType(heapTest(arr1, arr1)), "Return type of heapTest is bool");

    // Test operator usage (tests pass if code compiles)
    OnlyLessThan arr2[10];
    OnlyLessThan arrc2[10];
    heapInsert(arr2, arr2+10);
    t.test(true, "heapInsert - compiles when value type has only operator<");
    heapDelete(arr2, arr2+10);
    t.test(true, "heapDelete - compiles when value type has only operator<");
    heapMake(arr2, arr2+10);
    t.test(true, "heapMake - compiles when value type has only operator<");
    heapSort(arr2, arr2+10);
    t.test(true, "heapSort - compiles when value type has only operator<");
    result = heapTest(arrc2, arrc2+10);
    t.test(true, "heapTest - compiles when value type has only operator<");

    // Test on alternate random-access range type (tests pass if code compiles)
    std::deque<double> d(10, 0.);
    const std::deque<double> dc(10, 0.);
    heapInsert(d.rbegin(), d.rend());
    t.test(true, "heapInsert - compiles with alt range type");
    heapDelete(d.rbegin(), d.rend());
    t.test(true, "heapDelete - compiles with alt range type");
    heapMake(d.rbegin(), d.rend());
    t.test(true, "heapMake - compiles with alt range type");
    heapSort(d.rbegin(), d.rend());
    t.test(true, "heapSort - compiles with alt range type");
    result = heapTest(dc.rbegin(), dc.rend());
    t.test(true, "heapTest - compiles with alt range type");
}


// test_heapalg_function_heapInsert
// Test suite for Heap algorithms, function heapInsert
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_heapalg_function_heapInsert(Tester & t)
{
    std::cout << "Test Suite: Heap algorithms - function heapInsert" << std::endl;

    // size 1 range tests
    {
        int data[11] = { 1, 2, 3, 4, 5, 50, 101, 102, 103, 104, 105 };
        heapInsert(data+5, data+6);
        const int data_result[11] = { 1, 2, 3, 4, 5, 50, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+11, data_result), "heapInsert - size 1 range test #1");
    }

    {
        int data[11] = { 105, 104, 103, 102, 101, 50, 5, 4, 3, 2, 1 };
        heapInsert(data+5, data+6);
        const int data_result[11] = { 105, 104, 103, 102, 101, 50, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+11, data_result), "heapInsert - size 1 range test #2");
    }

    // size 2 range tests
    {
        int data[12] = { 1, 2, 3, 4, 5, 50, 51, 101, 102, 103, 104, 105 };
        heapInsert(data+5, data+7);
        const int data_result[12] = { 1, 2, 3, 4, 5, 51, 50, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+12, data_result), "heapInsert - size 2 range test #1");
    }

    {
        int data[12] = { 105, 104, 103, 102, 101, 51, 50, 5, 4, 3, 2, 1 };
        heapInsert(data+5, data+7);
        const int data_result[12] = { 105, 104, 103, 102, 101, 51, 50, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+12, data_result), "heapInsert - size 2 range test #2");
    }

    // large range tests
    {
        int data[16] = { 1, 40, 30, 30, 20, 20, 20, 20, 10, 10, 10, 10, 25, 35, 45, 100 };

        heapInsert(data+1, data+12);
        const int data_result01[16] = { 1, 40, 30, 30, 20, 20, 20, 20, 10, 10, 10, 10, 25, 35, 45, 100 };
        t.test(std::equal(data, data+16, data_result01), "heapInsert - large range test #1");
       
        heapInsert(data+1, data+13);
        const int data_result02[16] = { 1, 40, 30, 30, 20, 20, 25, 20, 10, 10, 10, 10, 20, 35, 45, 100 };
        t.test(std::equal(data, data+16, data_result02), "heapInsert - large range test #2");
       
        heapInsert(data+1, data+14);
        const int data_result03[16] = { 1, 40, 30, 35, 20, 20, 30, 20, 10, 10, 10, 10, 20, 25, 45, 100 };
        t.test(std::equal(data, data+16, data_result03), "heapInsert - large range test #3");
       
        heapInsert(data+1, data+15);
        const int data_result04[16] = { 1, 45, 30, 40, 20, 20, 30, 35, 10, 10, 10, 10, 20, 25, 20, 100 };
        t.test(std::equal(data, data+16, data_result04), "heapInsert - large range test #4");
    }

    // Alternate random-access range type tests
    {
        const double data[16] = { 99., 99., 99., 99., 99., 99., 99., 99., 35., 15., 5., 10., 25., 20., 30., 1. };
        std::deque<double> d(data, data+16);
        heapInsert(d.rbegin()+1, d.rend()-8);
        const double data_result[16] = { 99., 99., 99., 99., 99., 99., 99., 99., 25., 15., 5., 10., 30., 20., 35., 1. };
        t.test(std::equal(d.begin(), d.end(), data_result), "heapInsert - alt range type test");
    }
}


// test_heapalg_function_heapDelete
// Test suite for Heap algorithms, function heapDelete
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_heapalg_function_heapDelete(Tester & t)
{
    std::cout << "Test Suite: Heap algorithms - function heapDelete" << std::endl;

    // size 1 range tests
    {
        int data[11] = { 1, 2, 3, 4, 5, 50, 101, 102, 103, 104, 105 };
        heapDelete(data+5, data+6);
        const int data_result[11] = { 1, 2, 3, 4, 5, 50, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+11, data_result), "heapDelete - size 1 range test #1");
    }

    {
        int data[11] = { 105, 104, 103, 102, 101, 50, 5, 4, 3, 2, 1 };
        heapDelete(data+5, data+6);
        const int data_result[11] = { 105, 104, 103, 102, 101, 50, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+11, data_result), "heapDelete - size 1 range test #2");
    }

    // size 2 range tests
    {
        int data[12] = { 1, 2, 3, 4, 5, 51, 50, 101, 102, 103, 104, 105 };
        heapDelete(data+5, data+7);
        const int data_result[12] = { 1, 2, 3, 4, 5, 50, 51, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+12, data_result), "heapDelete - size 2 range test #1");
    }

    {
        int data[12] = { 105, 104, 103, 102, 101, 51, 50, 5, 4, 3, 2, 1 };
        heapDelete(data+5, data+7);
        const int data_result[12] = { 105, 104, 103, 102, 101, 50, 51, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+12, data_result), "heapDelete - size 2 range test #2");
    }

    // large range tests
    {
        int data[32] = { 1, 70, 65, 60, 40, 35, 45, 55, 5, 15, 20, 10, 25, 30, 50, 99,
                         99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };

        heapDelete(data+1, data+15);
        const int data_result01[32] = { 1, 65, 50, 60, 40, 35, 45, 55, 5, 15, 20, 10, 25, 30, 70, 99,
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        t.test(std::equal(data, data+32, data_result01), "heapDelete - large range test #1");

        heapDelete(data+1, data+14);
        const int data_result02[32] = { 1, 60, 50, 55, 40, 35, 45, 30, 5, 15, 20, 10, 25, 65, 70, 99,
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        t.test(std::equal(data, data+32, data_result02), "heapDelete - large range test #2");

        heapDelete(data+1, data+13);
        const int data_result03[32] = { 1, 55, 50, 45, 40, 35, 25, 30, 5, 15, 20, 10, 60, 65, 70, 99,
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        t.test(std::equal(data, data+32, data_result03), "heapDelete - large range test #3");

        heapDelete(data+1, data+12);
        const int data_result04[32] = { 1, 50, 40, 45, 15, 35, 25, 30, 5, 10, 20, 55, 60, 65, 70, 99,
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        t.test(std::equal(data, data+32, data_result04), "heapDelete - large range test #4");
    }

    // Alternate random-access range type tests
    {
        const double data[16] = { 99., 99., 99., 99., 99., 99., 99., 99., 25., 15., 5., 10., 30., 20., 35., 1. };
        std::deque<double> d(data, data+16);
        heapDelete(d.rbegin()+1, d.rend()-8);
        const double data_result[16] = { 99., 99., 99., 99., 99., 99., 99., 99., 35., 15., 5., 10., 25., 20., 30., 1. };
        t.test(std::equal(d.begin(), d.end(), data_result), "heapDelete - alt range type test");
    }
}


// test_heapalg_function_heapMake
// Test suite for Heap algorithms, function heapMake
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_heapalg_function_heapMake(Tester & t)
{
    std::cout << "Test Suite: Heap algorithms - function heapMake" << std::endl;

    // Empty range tests
    {
        int data[10] = { 1, 2, 3, 4, 5, 101, 102, 103, 104, 105 };
        heapMake(data+5, data+5);
        const int data_result[10] = { 1, 2, 3, 4, 5, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+10, data_result), "heapMake - empty range test #1");
    }

    {
        int data[10] = { 105, 104, 103, 102, 101, 5, 4, 3, 2, 1 };
        heapMake(data+5, data+5);
        const int data_result[10] = { 105, 104, 103, 102, 101, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+10, data_result), "heapMake - empty range test #2");
    }

    // size 1 range tests
    {
        int data[11] = { 1, 2, 3, 4, 5, 50, 101, 102, 103, 104, 105 };
        heapMake(data+5, data+6);
        const int data_result[11] = { 1, 2, 3, 4, 5, 50, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+11, data_result), "heapMake - size 1 range test #1");
    }

    {
        int data[11] = { 105, 104, 103, 102, 101, 50, 5, 4, 3, 2, 1 };
        heapMake(data+5, data+6);
        const int data_result[11] = { 105, 104, 103, 102, 101, 50, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+11, data_result), "heapMake - size 1 range test #2");
    }

    // size 2 range tests
    {
        int data[12] = { 1, 2, 3, 4, 5, 50, 51, 101, 102, 103, 104, 105 };
        heapMake(data+5, data+7);
        const int data_result[12] = { 1, 2, 3, 4, 5, 51, 50, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+12, data_result), "heapMake - size 2 range test #1");
    }

    {
        int data[12] = { 105, 104, 103, 102, 101, 51, 50, 5, 4, 3, 2, 1 };
        heapMake(data+5, data+7);
        const int data_result[12] = { 105, 104, 103, 102, 101, 51, 50, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+12, data_result), "heapMake - size 2 range test #2");
    }

    // large range tests
    {
        int data[32] = { 1, 50, 20, 30, 55, 60, 15, 25, 45, 65, 70, 40, 5, 10, 35, 99,
                         99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };

        heapMake(data+1, data+15);
        const int data_result[32] = { 1, 70, 65, 35, 55, 60, 15, 30, 45, 50, 20, 40, 5, 10, 25, 99,
                                        99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        t.test(std::equal(data, data+32, data_result), "heapMake - large range test");
    }

    // Alternate random-access range type tests
    {
        const double data[16] = { 99., 99., 99., 99., 99., 99., 99., 99., 5., 15., 20., 30., 35., 25., 10., 1. };
        std::deque<double> d(data, data+16);
        heapMake(d.rbegin()+1, d.rend()-8);
        const double data_result[16] = { 99., 99., 99., 99., 99., 99., 99., 99., 5., 10., 20., 25., 15., 30., 35., 1. };
        t.test(std::equal(d.begin(), d.end(), data_result), "heapMake - alt range type test");
    }
}


// test_heapalg_function_heapSort
// Test suite for Heap algorithms, function heapSort
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_heapalg_function_heapSort(Tester & t)
{
    std::cout << "Test Suite: Heap algorithms - function heapSort" << std::endl;

    // Empty range tests
    {
        int data[10] = { 1, 2, 3, 4, 5, 101, 102, 103, 104, 105 };
        heapSort(data+5, data+5);
        const int data_result[10] = { 1, 2, 3, 4, 5, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+10, data_result), "heapSort - empty range test #1");
    }

    {
        int data[10] = { 105, 104, 103, 102, 101, 5, 4, 3, 2, 1 };
        heapSort(data+5, data+5);
        const int data_result[10] = { 105, 104, 103, 102, 101, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+10, data_result), "heapSort - empty range test #2");
    }

    // size 1 range tests
    {
        int data[11] = { 1, 2, 3, 4, 5, 50, 101, 102, 103, 104, 105 };
        heapSort(data+5, data+6);
        const int data_result[11] = { 1, 2, 3, 4, 5, 50, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+11, data_result), "heapSort - size 1 range test #1");
    }

    {
        int data[11] = { 105, 104, 103, 102, 101, 50, 5, 4, 3, 2, 1 };
        heapSort(data+5, data+6);
        const int data_result[11] = { 105, 104, 103, 102, 101, 50, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+11, data_result), "heapSort - size 1 range test #2");
    }

    // size 2 range tests
    {
        int data[12] = { 1, 2, 3, 4, 5, 51, 50, 101, 102, 103, 104, 105 };
        heapSort(data+5, data+7);
        const int data_result[12] = { 1, 2, 3, 4, 5, 50, 51, 101, 102, 103, 104, 105 };
        t.test(std::equal(data, data+12, data_result), "heapSort - size 2 range test #1");
    }

    {
        int data[12] = { 105, 104, 103, 102, 101, 51, 50, 5, 4, 3, 2, 1 };
        heapSort(data+5, data+7);
        const int data_result[12] = { 105, 104, 103, 102, 101, 50, 51, 5, 4, 3, 2, 1 };
        t.test(std::equal(data, data+12, data_result), "heapSort - size 2 range test #2");
    }

    // large range tests
    {
        int data[32] = { 1, 70, 65, 35, 55, 60, 15, 30, 45, 50, 20, 40, 5, 10, 25, 99,
                         99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        heapSort(data+1, data+15);
        int data_result[32] = { 1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 99,
                                  99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        t.test(std::equal(data, data+32, data_result), "heapSort - large range test #1");
    }

    {
        int data[32] = { 99, 70, 65, 35, 55, 60, 15, 30, 45, 50, 20, 40, 5, 10, 25, 1,
                         1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        heapSort(data+1, data+15);
        int data_result[32] = { 99, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 1,
                                  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        t.test(std::equal(data, data+32, data_result), "heapSort - large range test #2");
    }

    // Alternate random-access range type tests
    {
        const double data[16] = { 99., 99., 99., 99., 99., 99., 99., 99., 25., 15., 5., 10., 30., 20., 35., 1. };
        std::deque<double> d(data, data+16);
        heapSort(d.rbegin()+1, d.rend()-8);
        const double data_result[16] = { 99., 99., 99., 99., 99., 99., 99., 99., 35., 30., 25., 20., 15., 10., 5., 1. };
        t.test(std::equal(d.begin(), d.end(), data_result), "heapSort - alt range type test");
    }
}


// test_heapalg_function_heapTest
// Test suite for Heap algorithms, function heapTest
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_heapalg_function_heapTest(Tester & t)
{
    std::cout << "Test Suite: Heap algorithms - function heapTest" << std::endl;

    bool result;  // For return value of heapTest

    // Empty range tests
    {
        const int data[10] = { 1, 2, 3, 4, 5, 101, 102, 103, 104, 105 };
        result = heapTest(data+5, data+5);
        t.test(result, "heapTest - empty range test #1");
    }

    {
        const int data[10] = { 105, 104, 103, 102, 101, 5, 4, 3, 2, 1 };
        result = heapTest(data+5, data+5);
        t.test(result, "heapTest - empty range test #2");
    }

    // size 1 range tests
    {
        const int data[11] = { 1, 2, 3, 4, 5, 50, 101, 102, 103, 104, 105 };
        result = heapTest(data+5, data+6);
        t.test(result, "heapTest - size 1 range test #1");
    }

    {
        const int data[11] = { 105, 104, 103, 102, 101, 50, 5, 4, 3, 2, 1 };
        result = heapTest(data+5, data+6);
        t.test(result, "heapTest - size 1 range test #2");
    }

    // size 2 range tests
    {
        const int data[12] = { 1, 2, 3, 4, 5, 50, 51, 101, 102, 103, 104, 105 };
        result = heapTest(data+5, data+7);
        t.test(!result, "heaptest - size 2 range test #1 (not Heap)");
    }

    {
        const int data[12] = { 1, 2, 3, 4, 5, 51, 50, 101, 102, 103, 104, 105 };
        result = heapTest(data+5, data+7);
        t.test(result, "heaptest - size 2 range test #2 (Heap, strict)");
    }

    {
        const int data[12] = { 1, 2, 3, 4, 5, 50, 50, 101, 102, 103, 104, 105 };
        result = heapTest(data+5, data+7);
        t.test(result, "heaptest - size 2 range test #3 (Heap, non-strict)");
    }

    {
        const int data[12] = { 105, 104, 103, 102, 101, 50, 51, 5, 4, 3, 2, 1 };
        result = heapTest(data+5, data+7);
        t.test(!result, "heaptest - size 2 range test #4 (not Heap)");
    }

    {
        const int data[12] = { 105, 104, 103, 102, 101, 51, 50, 5, 4, 3, 2, 1 };
        result = heapTest(data+5, data+7);
        t.test(result, "heaptest - size 2 range test #5 (Heap, strict)");
    }

    {
        const int data[12] = { 105, 104, 103, 102, 101, 50, 50, 5, 4, 3, 2, 1 };
        result = heapTest(data+5, data+7);
        t.test(result, "heaptest - size 2 range test #6 (Heap, non-strict)");
    }

    // large range tests
    {
        const int data[32] = { 99, 65, 70, 60, 40, 45, 50, 55, 5, 10, 15, 20, 25, 30, 35, 1,
                               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        result = heapTest(data+1, data+15);
        t.test(!result, "heapTest - large range test #1 (not Heap)");
    }

    {
        const int data[32] = { 99, 70, 60, 65, 40, 45, 50, 35, 5, 10, 15, 20, 25, 30, 55, 1,
                               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        result = heapTest(data+1, data+15);
        t.test(!result, "heapTest - large range test #2 (not Heap)");
    }

    {
        const int data[32] = { 1, 70, 60, 65, 40, 45, 50, 55, 5, 10, 15, 20, 25, 30, 35, 99,
                               99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        result = heapTest(data+1, data+15);
        t.test(result, "heapTest - large range test #3 (Heap, strict)");
    }

    {
        const int data[32] = { 1, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 99,
                               99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        result = heapTest(data+1, data+15);
        t.test(result, "heapTest - large range test #4 (Heap, non-strict)");
    }

    // Alternate random-access range type tests
    {
        const int data[32] = { 99, 65, 70, 60, 40, 45, 50, 55, 5, 10, 15, 20, 25, 30, 35, 1,
                               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        std::deque<double> d(data, data+32);
        std::reverse(d.begin(), d.end());
        result = heapTest(d.rbegin()+1, d.rend()-17);
        t.test(!result, "heapTest - alt range type test #1 (not Heap)");
    }

    {
        const int data[32] = { 99, 70, 60, 65, 40, 45, 50, 35, 5, 10, 15, 20, 25, 30, 55, 1,
                               1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        std::deque<double> d(data, data+32);
        std::reverse(d.begin(), d.end());
        result = heapTest(d.rbegin()+1, d.rend()-17);
        t.test(!result, "heapTest - alt range type test #2 (not Heap)");
    }

    {
        const int data[32] = { 1, 70, 60, 65, 40, 45, 50, 55, 5, 10, 15, 20, 25, 30, 35, 99,
                               99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        std::deque<double> d(data, data+32);
        std::reverse(d.begin(), d.end());
        result = heapTest(d.rbegin()+1, d.rend()-17);
        t.test(result, "heapTest - alt range type test #3 (Heap, strict)");
    }

    {
        const int data[32] = { 1, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 99,
                               99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99, 99 };
        std::deque<double> d(data, data+32);
        std::reverse(d.begin(), d.end());
        result = heapTest(d.rbegin()+1, d.rend()-17);
        t.test(result, "heapTest - alt range type test #4 (Heap, non-strict)");
    }
}


// test_heapalg
// Test suite for Heap algorithms
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_heapalg(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR Heap algorithms" << std::endl;
    test_heapalg_types(t);
    test_heapalg_function_heapInsert(t);
    test_heapalg_function_heapDelete(t);
    test_heapalg_function_heapMake(t);
    test_heapalg_function_heapSort(t);
    test_heapalg_function_heapTest(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs Heap Algorithms test suite, prints results to cout.
int main()
{
    Tester t;
    test_heapalg(t);

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

