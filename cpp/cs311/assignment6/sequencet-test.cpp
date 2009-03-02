// sequencet-test.cpp
// Glenn G. Chappell
// 2 Nov 2006
//
// For CS 311
// Used in Assignment 6
// Test file for class SequenceT

// Note: Exceptions thrown and exception-safety conditions in this program
// are based on the assumption that the SequenceT class is correctly
// written.

#include "sequencet.h"  // For class SequenceT
// Include above BEFORE system files, to make sure it works by itself
#include "sequencet.h"  // Double inclusion test

#include <iostream>   // for std::cout, std::endl
#include <string>     // for std::string
#include <stdexcept>  // for std::range_error
#include <cstdlib>    // for std::size_t
#include <algorithm>  // for std::copy, std::equal

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
// Item class for testing
// ************************************************************************

// class TestItem
// Item type for testing class SequenceT
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
    // Does not throw (No-Throw Guarantee)
    TestItem()
    { ++testItemCount_; }

    // Dctor
    // Pre: None.
    // Post:
    //     (testItemCount_ has been incremented.)
    // Does not throw (No-Throw Guarantee)
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
    // Does not throw (No-Throw Guarantee)
    static void resetCount()
    { testItemCount_ = 0; }

    // getCount
    // Pre: None.
    // Post:
    //     return == testItemCount_.
    // Does not throw (No-Throw Guarantee)
    static int getCount()
    { return testItemCount_; }

// ***** TestItem: Data Members *****
private:

    static int testItemCount_;  // Counts default ctor, dctor calls

};  // End class TestItem

// Definition of static data member of class TestItem
int TestItem::testItemCount_ = 0;

// ************************************************************************
// Item class for testing exception handling
// ************************************************************************

// class TestItem2
// Item type for testing class SequenceT
// Copy operations throw.
// Invariants: None.
class TestItem2 {

// ***** TestItem2: Ctors, dctor, op= *****
public:

    // Default ctor
    // Does nothing, but we must write it, since we write a ctor.
    // Pre: None.
    // Post: None.
    // Does not throw (No-Throw Guarantee)
    TestItem2()
    {}

    // Copy ctor
    // Throws std::range_error with message "A".
    // Pre: None.
    // Post: None.
    // Throws std::range_error. Strong Guarantee.
    TestItem2(const TestItem2 & other)
    {
        throw std::range_error("A");
    }

    // Copy assignment
    // Throws std::range_error with message "A".
    // Pre: None.
    // Post: None.
    // Throws std::range_error. Strong Guarantee.
    TestItem2 & operator=(const TestItem2 & rhs)
    {
        throw std::range_error("A");
    }

    // Compiler-generated dctor is used.

};  // End class TestItem2


// ************************************************************************
// Class for type checking
// ************************************************************************

// class MustBe
// This class exists in order to have static member function checkType,
// which takes a parameter of a given type, by reference. Objects of type
// MustBe<T> cannot be created.
// Usage:
//     MustBe<MyType>::checkType(x)
//     does not compile if the type of x is neither (MyType) nor
//     (const MyType). If the former, then the function returns true; if
//     the latter, then the function returns false.
// Invariants: None.
// Requirements on Types:
//     T is not a const type; that is, (T) and (const T) are distinct.
template<typename T>
class MustBe {

public:

    // checkType
    // ZZZ
    // Does not throw (No-Throw Guarantee)
    static bool checkType(T & dummy)
    { return true; }

    // checkType
    // ZZZ
    // Does not throw (No-Throw Guarantee)
    static bool checkType(const T & dummy)
    { return false; }

private:

    // Uncopyable class. Do not define copy ctor, copy assn.
    MustBe(const MustBe &);
    MustBe<T> & operator=(const MustBe &);

    // Compiler-generated dctor is used (but irrelevant).

};  // End class MustBe

// ************************************************************************
// Test Suite Functions
// ************************************************************************

// test_class_SequenceT_size_empty_and_ctor_from_size
// Test suite for class SequenceT, functions size, empty, and ctor from size
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_size_empty_and_ctor_from_size(Tester & t)
{
    std::cout << "Test Suite: class SequenceT - function size, ctor from size" << std::endl;

    const SequenceT<int> sti1(0);
    t.test(sti1.size() == 0, "size, ctor from size (const) #1");
    t.test(sti1.empty(), "empty, ctor from size (const) #1");

    const SequenceT<int> sti2(10);
    t.test(sti2.size() == 10, "size, ctor from size (const) #2");
    t.test(!sti2.empty(), "empty, ctor from size (const) #2");

    const SequenceT<double> std(100);
    t.test(std.size() == 100, "size, ctor from size (const) #3)");
    t.test(!std.empty(), "empty, ctor from size (const) #3)");

    SequenceT<int> sti3(20);
    t.test(sti3.size() == 20, "size, ctor from size (non-const)");
    t.test(!sti3.empty(), "size, ctor from size (non-const)");
}


// test_class_SequenceT_default_ctor
// Test suite for class SequenceT, default ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_default_ctor(Tester & t)
{
    std::cout << "Test Suite: class SequenceT - default ctor" << std::endl;

    const SequenceT<int> sti1;
    t.test(sti1.size() == 0, "default ctor, size");
    t.test(sti1.empty(), "default ctor, empty");
}


// test_class_SequenceT_bracket_op
// Test suite for class Product, bracket operator
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_bracket_op(Tester & t)
{
    std::cout << "Test Suite: class Product, bracket operator" << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SequenceT<int> sti(theSize);
    for (i = 0; i < theSize; ++i)
        sti[i] = 15 - i * i;

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (sti[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (non-const) #1");

    sti[2] = 1000;
    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (sti[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (non-const) #2");

    // Make const version, no copy
    const SequenceT<int> & stiRef = sti;

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiRef[i] != ((i == 2) ? 1000 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "Bracket operator (const)");
}


// test_class_SequenceT_copy_ctor
// Test suite for class SequenceT, copy ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class SequenceT - copy ctor" << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SequenceT<int> sti(theSize);
    for (i = 0; i < theSize; ++i)
        sti[i] = 15 - i * i;

    // Make const version, no copy
    const SequenceT<int> & stiRef = sti;
    // Make copy (copy ctor)
    const SequenceT<int> stiCopy(stiRef);

    t.test(stiCopy.size() == theSize, "Copy ctor - check size");

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy ctor - check values");

    SequenceT<int> stiCopy2(stiRef);
    sti[0] = 1;
    t.test(stiCopy2[0] == 15 - 0 * 0, "Copy ctor - change value #1");

    stiCopy2[0] = 2;
    t.test(sti[0] == 1, "Copy ctor - change value #2");
}


// test_class_SequenceT_copy_assn
// Test suite for class SequenceT, copy assignment
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class SequenceT - copy assignment" << std::endl;

    const int theSize = 10;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SequenceT<int> sti(theSize);
    for (i = 0; i < theSize; ++i)
        sti[i] = 15 - i * i;

    // Make const version, no copy
    const SequenceT<int> & stiRef = sti;
    // Make copy (copy assignment)
    SequenceT<int> stiCopy(1);
    stiCopy = stiRef;

    t.test(stiCopy.size() == theSize, "Copy assignment - check size");

    noErrors = true;
    for (i = 0; i < theSize; ++i)
    {
        if (stiCopy[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Copy assignment - check values");

    SequenceT<int> stiCopy2(stiRef);
    sti[0] = 1;
    t.test(stiCopy2[0] == 15 - 0 * 0, "Copy assignment - change value #1");

    stiCopy2[0] = 2;
    t.test(sti[0] == 1, "Copy assignment - change value #2");
}


// test_class_SequenceT_resize
// Test suite for class SequenceT, function resize
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_resize(Tester & t)
{
    std::cout << "Test Suite: class SequenceT - resize" << std::endl;

    const int theSize1 = 20;
    const int theSize2 = 10;
    const int theSize3 = 500;
    const int theSize4 = 100000;
    bool noErrors;  // True if no errors encountered
    int i;          // Counter

    SequenceT<int> sti(theSize1);
    for (i = 0; i < theSize1; ++i)
        sti[i] = 15 - i * i;

    sti.resize(theSize2);
    t.test(sti.size() == theSize2, "Resize - reduce size, check size");
    t.test(!sti.empty(), "Resize - reduce size, check empty");

    noErrors = true;
    for (i = 0; i < theSize2; ++i)
    {
        if (sti[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Resize - reduce size, check values");

    sti.resize(theSize3);
    t.test(sti.size() == theSize3, "Resize - increase size, check size");
    t.test(!sti.empty(), "Resize - increase size, check empty");

    noErrors = true;
    for (i = 0; i < theSize2; ++i)
    {
        if (sti[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Resize - increase size, check values");

     sti.resize(theSize4);
    t.test(sti.size() == theSize4, "Resize - increase size greatly, check size");
    t.test(!sti.empty(), "Resize - increase size greatly, check empty");

    noErrors = true;
    for (i = 0; i < theSize2; ++i)
    {
        if (sti[i] != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "Resize - increase size greatly, check values");

   sti.resize(0);
    t.test(sti.size() == 0, "Resize - size zero, check size");
    t.test(sti.empty(), "Resize - size zero, check empty");
}


// test_class_SequenceT_begin_end
// Test suite for class SequenceT, functions begin & end
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_begin_end(Tester & t)
{
    std::cout << "Test Suite: class SequenceT - functions begin & end" << std::endl;

    const int theSize = 10;
    bool noErrors;      // True if no errors encountered
    int i;              // Counter
    int * iter;         // iterator
    const int * citer;  // const_iterator

    SequenceT<int> sti(theSize);
    for (iter = sti.begin(), i = 0; iter != sti.end(); ++iter, ++i)
        *iter = 15 - i * i;

    // Non-const test
    t.test(sti.begin() != sti.end(), "begin/end - inequality (non-const)");
    t.test(sti.end() - sti.begin() == theSize, "begin/end - check difference (non-const)");
    noErrors = true;
    for (iter = sti.begin(), i = 0; iter != sti.end(); ++iter, ++i)
    {
        if (*iter != 15 - i * i)
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check values (non-const)");

    // Dereference and use to assign
    *(sti.begin()) = 1001;
    *(sti.end() - 1) = 1002;
    noErrors = true;
    for (iter = sti.begin(), i = 0; iter != sti.end(); ++iter, ++i)
    {
        if (*iter != ((i == 0) ? 1001 : (i == theSize-1) ? 1002 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check modification of values (non-const)");

    // Make const version, no copy
    const SequenceT<int> & stiRef = sti;

    // Const test
    t.test(stiRef.begin() != stiRef.end(), "begin/end - inequality (const)");
    t.test(stiRef.end() - stiRef.begin() == theSize, "begin/end - check difference (const)");
    noErrors = true;
    for (citer = stiRef.begin(), i = 0; citer != stiRef.end(); ++citer, ++i)
    {
        if (*citer != ((i == 0) ? 1001 : (i == theSize-1) ? 1002 : 15 - i * i))
            noErrors = false;
    }
    t.test(noErrors, "begin/end - check values (const)");

    const SequenceT<int> sti2;
    t.test(sti2.begin() == sti2.end(), "begin/end - check equality, default constructed (const)");
    SequenceT<int> sti3;
    t.test(sti3.begin() == sti3.end(), "begin/end - check equality, default constructed (non-const)");
}


// test_class_SequenceT_insert_del
// Test suite for class SequenceT, functions insert & del
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_insert_del(Tester & t)
{
    std::cout << "Test Suite: class SequenceT - functions insert & del" << std::endl;

    const int SIZE = 15;
    int arr1[SIZE] = { 10, 1, 15, 7, 13, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };

    SequenceT<int> sti(SIZE);
    std::copy(arr1, arr1+SIZE, sti.begin());

    sti.insert(101, 2);
    int arr2[SIZE+1] = { 10, 1, 101, 15, 7, 13, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };
    t.test(sti.size() == SIZE+1, "insert - check size");
    t.test(!sti.empty(), "insert - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr2), "insert - check values");

    sti.del(5);
    int arr3[SIZE] = { 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };
    t.test(sti.size() == SIZE, "del - check size");
    t.test(!sti.empty(), "del - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr3), "del - check values");

    sti.insert(102, 0);
    int arr4[SIZE+1] = { 102, 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };
    t.test(sti.size() == SIZE+1, "insert at beginning - check size");
    t.test(!sti.empty(), "insert at beginning - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr4), "insert at beginning - check values");

    sti.insert(103, sti.size());
    int arr5[SIZE+2] = { 102, 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9, 103 };
    t.test(sti.size() == SIZE+2, "insert at end - check size");
    t.test(!sti.empty(), "insert at end - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr5), "insert at end - check values");

    sti.del(0);
    int arr6[SIZE+1] = { 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9, 103 };
    t.test(sti.size() == SIZE+1, "del at beginning - check size");
    t.test(!sti.empty(), "del at beginning - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr6), "del at beginning - check values");

    sti.del(sti.size()-1);
    int arr7[SIZE] = { 10, 1, 101, 15, 7, 2, 11, 12, 6, 3, 8, 4, 15, 5, 9 };
    t.test(sti.size() == SIZE, "del at end - check size");
    t.test(!sti.empty(), "del at end - check empty");
    t.test(std::equal(sti.begin(), sti.end(), arr7), "del at end - check values");
}


// test_class_SequenceT_ctor_dctor_count
// Test suite for class SequenceT, number of class to item type
//  ctor, dctor.
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_ctor_dctor_count(Tester & t)
{
    std::cout << "Test Suite: class SequenceT - ctor, dctor count" << std::endl;

    // Check number of value type ctor/dctor calls on array creation & destruction
    TestItem::resetCount();
    int ctorCallCount;  // Holds number of default ctor calls
    { // Block, so we get dctor calls before function ends
        const SequenceT<TestItem> stt(10);
        ctorCallCount = TestItem::getCount();
        t.test(ctorCallCount >= 10, "Counting default ctor calls due to array creation");

        TestItem::resetCount();
    }
    t.test(TestItem::getCount() == ctorCallCount, "Counting dctor calls due to destruction");

    // Check number of value type ctor/dctor calls on self-assignment
    SequenceT<TestItem> stt2(10);
    TestItem::resetCount();
    stt2 = stt2;
    t.test(TestItem::getCount() == 0, "Self-assignment should generate no ctor/dctor calls");
}


// test_class_SequenceT_exceptions
// Test suite for class SequenceT, exception handling
//  ctor, dctor.
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_exceptions(Tester & t)
{
    std::cout << "Test Suite: class SequenceT - exceptions" << std::endl;

    const int theSize1 = 10;
    const int theSize2 = 100000;
       // We assume that theSize2 exceeds the capacity of a SequenceT created
       // with size theSize1. Of course, this may actually be false; we're
       // cheating slightly.
    bool gotException;
    bool correctType;

    SequenceT<TestItem2> stt1(theSize1);

    gotException = false;
    correctType = false;
    try
    {
        // Copy construction. Should throw.
        const SequenceT<TestItem2> stt2(stt1);
    }
    catch (std::range_error & e)
    {
        gotException = true;
        correctType = true;
        t.test(std::string(e.what()) == "A", "Exceptions - exception #1 message");
    }
    catch (...)
    {
        gotException = true;
        correctType = false;
    }
    t.test(correctType, "Exceptions - exception #1 type");
    t.test(gotException, "Exceptions - exception #1 thrown");

    gotException = false;
    correctType = false;
    try
    {
        // Copy assignment. Should throw.
        SequenceT<TestItem2> stt3;
        stt3 = stt1;
    }
    catch (std::range_error & e)
    {
        gotException = true;
        correctType = true;
        t.test(std::string(e.what()) == "A", "Exceptions - exception #2 message");
    }
    catch (...)
    {
        gotException = true;
        correctType = false;
    }
    t.test(correctType, "Exceptions - exception #2 type");
    t.test(gotException, "Exceptions - exception #2 thrown");

    gotException = false;
    correctType = false;
    try
    {
        // Resize larger. Should throw, due to reallocate-and-copy.
        stt1.resize(theSize2);
    }
    catch (std::range_error & e)
    {
        gotException = true;
        correctType = true;
        t.test(std::string(e.what()) == "A", "Exceptions - exception #3 message");
        t.test(stt1.size() == theSize1, "Exceptions - resize Strong Guarantee");
    }
    catch (...)
    {
        gotException = true;
        correctType = false;
    }
    t.test(correctType, "Exceptions - exception #3 type");
    t.test(gotException, "Exceptions - exception #3 thrown");

    gotException = false;
    try
    {
        // Resize - not larger. Should NOT throw.
        stt1.resize(theSize1);
    }
    catch (...)
    {
        gotException = true;
    }
    t.test(!gotException, "Exceptions - exception #4 should not be thrown");
}


// test_class_SequenceT_types
// Test suite for class Product, types
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT_types(Tester & t)
{
    std::cout << "Test Suite: class Product, types" << std::endl;

    SequenceT<int> sti1(10);
    SequenceT<double> std1(10);
    const SequenceT<double> std2(10);
    bool check;

    // MEMBER TYPE value_type
    // Check existence
    // (Passes if code compiles)
    SequenceT<int>::value_type valtype1;
    t.test(true, "Member type value_type exists");

    // Check correctness
    // (Test fails if const is wrong; other problems cause compiler error)
    check = MustBe<int>::checkType(valtype1);
    t.test(check, "Member type value_type is correct (#1)");

    SequenceT<double>::value_type valtype2;
    check = MustBe<double>::checkType(valtype2);
    t.test(check, "Member type value_type is correct (#2)");

    // MEMBER TYPE size_type
    // Check existence
    // (Passes if code compiles)
    SequenceT<int>::size_type sizetype1;
    t.test(true, "Member type size_type exists");

    // Check correctness
    // (Test fails if const is wrong; other problems cause compiler error)
    check = MustBe<std::size_t>::checkType(sizetype1);
    t.test(check, "Member type size_type is correct (#1)");

    SequenceT<double>::size_type sizetype2;
    check = MustBe<std::size_t>::checkType(sizetype2);
    t.test(check, "Member type size_type is correct (#2)");

    // MEMBER TYPE iterator
    // Check existence
    // (Passes if code compiles)
    SequenceT<int>::iterator iter1;
    t.test(true, "Member type iterator exists");

    // Check correctness
    // (Test fails if const is wrong; other problems cause compiler error)
    check = MustBe<int *>::checkType(iter1);
    t.test(check, "Member type iterator is correct (#1)");

    SequenceT<double>::iterator iter2;
    check = MustBe<double *>::checkType(iter2);
    t.test(check, "Member type iterator is correct (#2)");

    // MEMBER TYPE const_iterator
    // Check existence
    // (Passes if code compiles)
    SequenceT<int>::iterator citer1;
    t.test(true, "Member type const_iterator exists");

    // Check correctness
    // (Test fails if const is wrong; other problems cause compiler error)
    check = MustBe<int *>::checkType(citer1);
    t.test(check, "Member type const_iterator is correct (#1)");

    SequenceT<double>::iterator citer2;
    check = MustBe<double *>::checkType(citer2);
    t.test(check, "Member type const_iterator is correct (#2)");

    // MEMBER FUNCTION bracket op
    // Check return type
    // (Test fails if const is wrong; other problems cause compiler error)
    MustBe<double>::checkType(std2[0]);  // ignore const-ness
    t.test(true, "Return type, bracket operator (const)");

    check = MustBe<double>::checkType(std1[0]);
    t.test(check, "Return type, bracket operator (non-const #1)");

    check = MustBe<int>::checkType(sti1[0]);
    t.test(check, "Return type, bracket operator (non-const #2)");

    // MEMBER FUNCTION size
    // Check return type
    // (Test passes if it compiles)
    MustBe<SequenceT<double>::size_type>::checkType(std1.size());  // ignore const-ness
    t.test(true, "Return type, function size");

    // MEMBER FUNCTION empty
    // Check return type
    // (Test passes if it compiles)
    MustBe<bool>::checkType(std1.empty());  // ignore const-ness
    t.test(true, "Return type, function empty");

    // MEMBER FUNCTION begin
    // Check return type
    // (Test fails if const is wrong; other problems cause compiler error)
    MustBe<SequenceT<double>::const_iterator>::checkType(std2.begin());  // ignore const-ness
    t.test(true, "Return type, function begin (const)");

    MustBe<SequenceT<double>::iterator>::checkType(std1.begin());  // ignore const-ness
    t.test(true, "Return type, function begin (non-const)");

    // MEMBER FUNCTION end
    // Check return type
    // (Test fails if const is wrong; other problems cause compiler error)
    MustBe<SequenceT<double>::const_iterator>::checkType(std2.end());  // ignore const-ness
    t.test(true, "Return type, function end (const)");

    MustBe<SequenceT<double>::iterator>::checkType(std1.end());  // ignore const-ness
    t.test(true, "Return type, function end (non-const)");
}


// test_class_SequenceT
// Test suite for class SequenceT
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_SequenceT(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS SequenceT" << std::endl;
    test_class_SequenceT_size_empty_and_ctor_from_size(t);
    test_class_SequenceT_default_ctor(t);
    test_class_SequenceT_bracket_op(t);
    test_class_SequenceT_copy_ctor(t);
    test_class_SequenceT_copy_assn(t);
    test_class_SequenceT_resize(t);
    test_class_SequenceT_begin_end(t);
    test_class_SequenceT_insert_del(t);
    test_class_SequenceT_ctor_dctor_count(t);
    test_class_SequenceT_exceptions(t);
    test_class_SequenceT_types(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs class SequenceT test suite, prints results to cout.
int main()
{
    Tester t;
    test_class_SequenceT(t);

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

