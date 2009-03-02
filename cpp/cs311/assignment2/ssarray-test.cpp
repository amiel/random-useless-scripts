// ssarray-test.cpp
// Glenn G. Chappell
// 15 Sep 2006
//
// For CS 311
// Used in Assignment 2
// Test file for class SSArray

#include "ssarray.h"  // For class SSArray
// Include above BEFORE system files, to make sure it works by itself
#include "ssarray.h"  // Double inclusion test

#include <iostream>  // for std::cout, std::endl
#include <string>    // for std::string

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
// Item class for testing
// ************************************************************************

// class TestItem
// Item type for testing class SSArray
// Increments static data member testItemCount
//  on default construction and destruction.
// Invariants:
//     TestItem::testItemCount_ is number of calls to default
//      ctor and/or dctor for all TestItem objects, since
//      most recent call to resetCount, or start of program
//      if resetCount has never been called.
class TestItem {

// ***** TestItem: Ctors, dctor, op= *****
public:

    // Default ctor
    // Pre: None.
    // Post:
    //     (testItemCount_ has been incremented.)
    TestItem()
    { ++testItemCount_; }

    // Dctor
    // Pre: None.
    // Post:
    //     (testItemCount_ has been incremented.)
    ~TestItem()
    { ++testItemCount_; }

    // Compiler-generated copy ctor, copy assignment used
    //  (and irrelevant).

// ***** TestItem: Functions dealing with count *****
public:

    // resetCount
    // Pre: None.
    // Post:
    //     testItemCount_ == 0.
    static void resetCount()
    { testItemCount_ = 0; }

    // getCount
    // Pre: None.
    // Post:
    //     return == testItemCount_.
    static int getCount()
    { return testItemCount_; }

// ***** TestItem: Data Members *****
private:

    static int testItemCount_;  // Counts default ctor, dctor calls

};  // End class TestItem

// Definition of static data member of class TestItem
int TestItem::testItemCount_ = 0;

// ************************************************************************
// Test Suite Functions
// ************************************************************************

// test_class_SSArray_size_and_ctor_from_size
// Test suite for class SSArray, function size and ctor from size
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_SSArray_size_and_ctor_from_size(Tester & t)
{
    std::cout << "Test Suite: class SSArray - function size, ctor from size" << std::endl;

    const SSArray<int> ssai(10);
    t.test(ssai.size() == 10, "size, ctor from size (const) #1");

    const SSArray<double> ssad(100);
    t.test(ssad.size() == 100, "size, ctor from size (const) #2)");

    SSArray<int> ssai2(20);
    t.test(ssai2.size() == 20, "size, ctor from size (non-const)");
}


// test_class_SSArray_bracket_op
// Test suite for class Product, bracket operator
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_SSArray_bracket_op(Tester & t)
{
    std::cout << "Test Suite: class Product, bracket operator" << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SSArray<int> ssai(theSize);
    for (i = 0; i < theSize; ++i)
        ssai[i] = 15 - i * i;

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (ssai[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (non-const)");

    // Make const version, no copy
    const SSArray<int> & ssaiRef = ssai;

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (ssaiRef[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (const)");
}


// test_class_SSArray_copy_ctor
// Test suite for class SSArray, copy ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_SSArray_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class SSArray - copy ctor" << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SSArray<int> ssai(theSize);
    for (i = 0; i < theSize; ++i)
        ssai[i] = 15 - i * i;

    // Make const version, no copy
    const SSArray<int> & ssaiRef = ssai;
    // Make copy (copy ctor)
    const SSArray<int> ssaiCopy(ssaiRef);

    t.test(ssaiCopy.size() == theSize, "Copy ctor - check size");

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (ssaiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - check values");
}


// test_class_SSArray_copy_assn
// Test suite for class SSArray, copy assignment
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_SSArray_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class SSArray - copy assignment" << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SSArray<int> ssai(theSize);
    for (i = 0; i < theSize; ++i)
        ssai[i] = 15 - i * i;

    // Make const version, no copy
    const SSArray<int> & ssaiRef = ssai;
    // Make copy (copy assignment)
    SSArray<int> ssaiCopy(1);
    ssaiCopy = ssaiRef;

    t.test(ssaiCopy.size() == theSize, "Copy assignment - check size");

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (ssaiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy assignment - check values");
}


// test_class_SSArray_begin_end
// Test suite for class SSArray, functions begin & end
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_SSArray_begin_end(Tester & t)
{
    std::cout << "Test Suite: class SSArray - functions begin & end" << std::endl;

    const int theSize = 10;
    bool noErrors;      // True if no errors encountered
    int i;              // Counter
    int * iter;         // iterator
    const int * citer;  // const_iterator

    SSArray<int> ssai(theSize);
    for (iter = ssai.begin(), i = 0; iter != ssai.end(); ++iter, ++i)
        *iter = 15 - i * i;

    // Non-const test
    t.test (ssai.end() - ssai.begin() == theSize, "begin/end - check difference (non-const)");
    noErrors = true;
    for (iter = ssai.begin(), i = 0; iter != ssai.end(); ++iter, ++i)
    {
        if (*iter != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check values (non-const)");

    // Make const version, no copy
    const SSArray<int> & ssaiRef = ssai;

    // Const test
    t.test(ssaiRef.end() - ssaiRef.begin() == theSize, "begin/end - check difference (const)");
    noErrors = true;
    for (citer = ssaiRef.begin(), i = 0; citer != ssaiRef.end(); ++citer, ++i)
    {
        if (*citer != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check values (const)");
}


// test_class_SSArray_comparisons
// Test suite for class SSArray, comparisons
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_SSArray_comparisons(Tester & t)
{
    std::cout << "Test Suite: class SSArray - comparisons" << std::endl;

    const int theSize = 10;
    int i;          // Counter

    SSArray<int> ssai1(theSize);
    for (i = 0; i < theSize; ++i)
        ssai1[i] = 15 - i * i;
    const SSArray<int> & ssai1Ref = ssai1;
    const SSArray<int> ssai2(theSize + 1);
    SSArray<int> ssai1Copy(ssai1Ref);

    // Check equality of copies
    t.test(ssai1 == ssai1Copy, "Equality of copies");

    // Check inequality of copies
    t.test(!(ssai1 != ssai1Copy), "Inequality of copies");

    // Check equality of different sizes (compilation checks constness of op==)
    t.test(!(ssai1Ref == ssai2), "Equality of different sizes");

    // Check inequality of different sizes (compilation checks constness of op!=)
    t.test(ssai1Ref != ssai2, "Inequality of different sizes");

    // Modify copy
    ++ssai1Copy[4];

    // Check equality of modification of copy
    t.test(!(ssai1 == ssai1Copy), "Equality of modification of copy");

    // Check inequality of modification of copy
    t.test(ssai1 != ssai1Copy, "Inequality of modification of copy");
}


// test_class_SSArray_ctor_dctor_count
// Test suite for class SSArray, number of class to item type
//  ctor, dctor.
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_SSArray_ctor_dctor_count(Tester & t)
{
    std::cout << "Test Suite: class SSArray - ctor, dctor count" << std::endl;

    // Check number of value type ctor/dctor calls on array creation & destruction
    TestItem::resetCount();
    { // Block, so we get dctor calls before function ends
        const SSArray<TestItem> ssat(10);

        t.test(TestItem::getCount() == 10, "Counting default ctor calls due to array creation");

        TestItem::resetCount();
    }
    t.test(TestItem::getCount() == 10, "Counting dctor calls after due to destruction");

    // Check number of value type ctor/dctor calls on self-assignment
    SSArray<TestItem> ssat2(10);
    TestItem::resetCount();
    ssat2 = ssat2;
    t.test(TestItem::getCount() == 0, "Self-assignment should generate no ctor/dctor calls");
}


// test_class_SSArray
// Test suite for class SSArray
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_SSArray(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS SSArray" << std::endl;
    test_class_SSArray_size_and_ctor_from_size(t);
    test_class_SSArray_bracket_op(t);
    test_class_SSArray_copy_ctor(t);
    test_class_SSArray_copy_assn(t);
    test_class_SSArray_begin_end(t);
    test_class_SSArray_comparisons(t);
    test_class_SSArray_ctor_dctor_count(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs class SSArray test suite, prints results to cout.
int main()
{
    Tester t;
    test_class_SSArray(t);

    std::cout << std::endl;
    if (t.allPassed())
        std::cout << "All tests successful" 
                  << std::endl;
    else
        std::cout << "Tests ********** UNSUCCESSFUL **********"
                  << std::endl;
    std::cout << std::endl;
}

