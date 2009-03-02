// dlist-test-pointer.cpp
// Revision 2
// Glenn G. Chappell
// 14 Nov 2006
//
// For CS 311
// Used in Assignment 7
// Test file for class DList - pointer version

#include "dlist.h"  // For class DList
// Include above BEFORE system files, to make sure it works by itself
#include "dlist.h"  // Double inclusion test

#include <iostream>   // for std::cout, std::endl
#include <string>     // for std::string
#include <cstdlib>    // for std::size_t
#include <sstream>    // for std::ostringstream

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
    // These two functions simulate a single function that takes either
    // a T or a const T, or an object of a type convertible to T, and
    // returns true if the object is in fact a T, and is not const.

    // checkType (reference to T)
    // Pre: None.
    // Post:
    //     Return is true.
    // Does not throw (No-Throw Guarantee)
    static bool checkType(T & dummy)
    { return true; }

    // checkType (reference-to-const to T)
    // Pre: None.
    // Post:
    //     Return is false.
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
// Functions to check DList size, values
// ************************************************************************

// checkDListEmpty
// Given a DList that should be empty, checks functions empty, size, and
// begin/end. The string s is a message describing the tests.
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void checkDListEmpty(const DList & d,
                     Tester & t,
                     const std::string & s)
{
    t.test(d.size() == 0, s + " - size");
    t.test(d.empty(), s + " - empty");
    t.test(d.begin() == d.end(), s + " - begin == end");
}

// CheckDListValues
// Given a DList that should have a certain size and values, checks
// functions empty, size, and begin/end, and does forward and backward
// iteration through entire DList, checking all values. The string s is
// a message describing the tests.
// Requirements on types:
//     BDIter must be a bidirectional iterator type
// Pre:
//     size >= 0.
//     Either size == 0,
//      or first points to the 1st item in a range of at least size
//      values.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
template <typename BDIter>
void checkDListValues(const DList & d,
                      BDIter first,
                      std::size_t size,
                      Tester & t,
                      const std::string & s)
{
    // Check size, empty, begin/end
    t.test(d.size() == size, s + " - size");

    if (size == 0)
    {
        t.test(d.empty(), s + " - empty");
        t.test(d.begin() == d.end(), s + " - begin == end");
        return;
    }

    t.test(!d.empty(), s + " - not empty");
    t.test(d.begin() != d.end(), s + " - begin != end");

    // Following tests only done when size != 0

    // Forward iteration
    BDIter valIter = first;
    DList::const_iterator cit = d.begin();
    DList::const_iterator cit2;
    for (int i = 0; i < size; ++i)
    {
        std::ostringstream oss;
        oss << (i+1);
        t.test(cit->item() == *valIter, s + " - iterate, item " + oss.str());
        t.test(cit != d.end(), s + " - iterate, not at end #" + oss.str());
        cit2 = cit;
        cit = cit->next();
        ++valIter;
    }
    t.test(cit == d.end(), s + " - iterate, at end");

    // Backward iteration
    cit = cit2;
    --valIter;
    for (int k = size-1; k >= 0; --k)
    {
        std::ostringstream oss;
        oss << (k+1);
        t.test(cit->item() == *valIter, s + " - backward iterate, item " + oss.str());
        cit2 = cit;
        cit = cit->prev();
        --valIter;
    }
    t.test(cit2 == d.begin(), s + " - backwards iterate, at begin");
}

// ************************************************************************
// Test Suite Functions
// ************************************************************************

// test_class_DList_types
// Test suite for class DList, types
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_DList_types(Tester & t)
{
    std::cout << "Test Suite: class DList - types" << std::endl;

    // Member types
    // Check DList::value_type
    DList::value_type vt;
    t.test(MustBe<int>::checkType(vt), "Member type value_type");

    // Check DList::size_type
    DList::size_type st;
    t.test(MustBe<std::size_t>::checkType(st), "Member type size_type");

    // Check DList::iterator
    DList::iterator it;
    t.test(MustBe<DList::Node *>::checkType(it), "Member type iterator");

    // Check DList::const_iterator
    DList::iterator cit;
    t.test(MustBe<const DList::Node *>::checkType(cit), "Member type const_iterator");

    // Return types (tests pass if code compiles)
    DList d1;
    const DList & rd1(d1);

    // Return type of empty
    MustBe<bool>::checkType(rd1.empty());
    t.test(true, "Return type of empty (const)");
    MustBe<bool>::checkType(d1.empty());
    t.test(true, "Return type of empty (non-const)");

    // Return type of size
    MustBe<std::size_t>::checkType(rd1.size());
    t.test(true, "Return type of size (const)");
    MustBe<std::size_t>::checkType(d1.size());
    t.test(true, "Return type of size (non-const)");

    // Return type of begin    
    MustBe<DList::const_iterator>::checkType(rd1.begin());
    t.test(true, "Return type of begin (const)");
    MustBe<DList::iterator>::checkType(d1.begin());
    t.test(true, "Return type of begin (non-const)");

    // Return type of end
    MustBe<DList::const_iterator>::checkType(rd1.end());
    t.test(true, "Return type of end (const)");
    MustBe<DList::iterator>::checkType(d1.end());
    t.test(true, "Return type of end (non-const)");
}


// test_class_DList_default_ctor
// Test suite for class DList, default ctor,
//  also partially tests functions empty, size, empty, begin, end
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_DList_default_ctor(Tester & t)
{
    std::cout << "Test Suite: class DList - default ctor" << std::endl;

    const DList d1;

    t.test(d1.empty(), "default ctor, empty (const)");
    t.test(d1.size() == 0, "default ctor, size (const)");
    t.test(d1.begin() == d1.end(), "default ctor, begin == end (const)");

    DList d2;
    checkDListEmpty(d2, t, "default ctor (const)");

}


// test_class_DList_insert_begin_end_iterators
// Test suite for class DList, insert, begin, end, iterators
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_DList_insert_begin_end_iterators(Tester & t)
{
    std::cout << "Test Suite: class DList - insert, begin, end" << std::endl;

    DList d1;
    const DList & rd1(d1);

    // Insert one item
    d1.insert(d1.begin(), 1);

    t.test(!d1.empty(), "Insert 1, not empty");
    t.test(d1.size() == 1, "Insert 1, size");

    // Check const_iterator to const object
    DList::const_iterator cit = rd1.begin();
    t.test(cit != rd1.end(), "Insert 1, const_iterator to const obj - begin != end");
    t.test(cit->item() == 1, "Insert 1, const_iterator to const obj - item");

    cit = cit->next();
    t.test(cit != rd1.begin(), "Increment const_iterator to const obj - citer != begin");
    t.test(cit == rd1.end(), "Increment const_iterator to const obj - citer == end");

    // Check const_iterator to non-const object
    cit = d1.begin();
    t.test(cit != d1.end(), "Insert 1, const_iterator to non-const obj - begin != end");
    t.test(cit->item() == 1, "Insert 1, const_iterator to non-const obj - item");

    cit = cit->next();
    t.test(cit != d1.begin(), "Increment const_iterator to non-const obj - citer != begin");
    t.test(cit == d1.end(), "Increment const_iterator to non-const obj - citer == end");

    // Check iterator
    DList::iterator it = d1.begin();
    t.test(it != d1.end(), "Insert 1, iterator - begin != end");
    t.test(it->item() == 1, "Insert 1, iterator - item");

    it = it->next();
    t.test(it != d1.begin(), "Increment iterator - iter != begin");
    t.test(it == d1.end(), "Increment iterator - iter == end");

    // Insert three more items
    d1.insert(d1.end(), 2);    // insert at end
    d1.insert(d1.begin(), 3);  // insert at beginning
    it = d1.begin();
    it = it->next();
    d1.insert(it, 4);          // insert in middle
    {
        int arr[] = { 3, 4, 1, 2 };
        checkDListValues(d1, arr, 4, t, "Insert 4");
    }
}


// test_class_DList_del
// Test suite for class DList, del
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_DList_del(Tester & t)
{
    std::cout << "Test Suite: class DList - del" << std::endl;

    DList d1;
    DList::iterator it;

    // Set up data
    d1.insert(d1.end(), 1);
    d1.insert(d1.end(), 2);
    d1.insert(d1.end(), 3);
    d1.insert(d1.end(), 4);
    d1.insert(d1.end(), 5);
    {
        int arr[] = { 1, 2, 3, 4, 5 };
        checkDListValues(d1, arr, 5, t, "Delete in middle");
    }


    // Delete at beginning
    d1.del(d1.begin());
    {
        int arr[] = { 2, 3, 4, 5 };
        checkDListValues(d1, arr, 4, t, "Delete at beginning");
    }

    // Delete in middle
    it = d1.begin();
    it = it->next();
    d1.del(it);
    {
        int arr[] = { 2, 4, 5 };
        checkDListValues(d1, arr, 3, t, "Delete in middle");
    }

    // Delete at end
    it = d1.begin();
    it = it->next();
    it = it->next();
    d1.del(it);
    {
        int arr[] = { 2, 4 };
        checkDListValues(d1, arr, 2, t, "Delete at end");
    }
}


// test_class_DList_copy_ctor
// Test suite for class DList, copy ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_DList_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class DList - copy constructor" << std::endl;

    DList d1;
    d1.insert(d1.begin(), 1);
    d1.insert(d1.end(), 2);
    d1.insert(d1.begin(), 3);
    d1.insert(d1.end(), 4);

    DList d2(d1);
    {
        int arr[] = { 3, 1, 2, 4 };
        checkDListValues(d2, arr, 4, t, "Copy ctor, check copy");
    }

    // Modify original, check copy
    d1.del(d1.begin());
    {
        int arr[] = { 3, 1, 2, 4 };
        checkDListValues(d2, arr, 4, t, "Modify original #2, check copy");
    }

    // Modify original #2, check copy
    d1.begin()->item() = 10;
    {
        int arr[] = { 3, 1, 2, 4 };
        checkDListValues(d2, arr, 4, t, "Modify original #2, check copy");
    }

    // Modify copy, check original
    d2.insert(d2.begin(), 5);
    {
        int arr[] = { 10, 2, 4 };
        checkDListValues(d1, arr, 3, t, "Modify copy, check original");
    }
}


// test_class_DList_copy_assn
// Test suite for class DList, copy assn
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_DList_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class DList - copy assignment" << std::endl;

    DList d1;
    d1.insert(d1.begin(), 1);
    d1.insert(d1.end(), 2);
    d1.insert(d1.begin(), 3);
    d1.insert(d1.end(), 4);

    DList d2;
    d2 = d1;
    {
        int arr[] = { 3, 1, 2, 4 };
        checkDListValues(d2, arr, 4, t, "Copy assn, check copy");
    }

    // Modify original, check copy
    d1.del(d1.begin());
    {
        int arr[] = { 3, 1, 2, 4 };
        checkDListValues(d2, arr, 4, t, "Modify original #2, check copy");
    }

    // Modify original #2, check copy
    d1.begin()->item() = 10;
    {
        int arr[] = { 3, 1, 2, 4 };
        checkDListValues(d2, arr, 4, t, "Modify original #2, check copy");
    }

    // Modify copy, check original
    d2.insert(d2.begin(), 5);
    {
        int arr[] = { 10, 2, 4 };
        checkDListValues(d1, arr, 3, t, "Modify copy, check original");
    }
}


// test_class_DList_swap
// Test suite for class DList, swap
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_DList_swap(Tester & t)
{
    std::cout << "Test Suite: class DList - swap" << std::endl;

    DList d1, d2;

    // Set up data
    d1.insert(d1.end(), 1);
    d1.insert(d1.end(), 2);
    d1.insert(d1.end(), 3);
    d1.insert(d1.end(), 4);

    d2.insert(d2.end(), 11);
    d2.insert(d2.end(), 12);

    // Do swap
    d1.swap(d2);

    // Check list 1
    {
        int arr[] = { 11, 12 };
        checkDListValues(d1, arr, 2, t, "list 1");
    }

    // Check list 2
    {
        int arr[] = { 1, 2, 3, 4 };
        checkDListValues(d2, arr, 4, t, "list 2");
    }
}


// test_class_DList_splice
// Test suite for class DList, splice
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_DList_splice(Tester & t)
{
    std::cout << "Test Suite: class DList - splice" << std::endl;

    DList d1, d2;
    DList::iterator it;

    // Set up data
    d1.insert(d1.end(), 1);
    d1.insert(d1.end(), 2);
    d1.insert(d1.end(), 3);
    d1.insert(d1.end(), 4);

    d2.insert(d2.end(), 11);
    d2.insert(d2.end(), 12);

    // Do splice
    it = d1.begin();
    it = it->next();
    d1.splice(it, d2);

    // Check list 2
    checkDListEmpty(d2, t, "list 2");

    // Check list 1
    {
        int arr[] = { 1, 11, 12, 2, 3, 4 };
        checkDListValues(d1, arr, 6, t, "list 1");
    }

    // self-splice
    d1.splice(d1.begin(), d1);

    // Check no change
    {
        int arr[] = { 1, 11, 12, 2, 3, 4 };
        checkDListValues(d1, arr, 6, t, "self-splice");
    }
}


// test_class_DList
// Test suite for class DList
// Uses other test-suite functions
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
// Does not throw (No-Throw Guarantee)
void test_class_DList(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS DList" << std::endl;
    test_class_DList_types(t);
    test_class_DList_default_ctor(t);
    test_class_DList_insert_begin_end_iterators(t);
    test_class_DList_del(t);
    test_class_DList_copy_ctor(t);
    test_class_DList_copy_assn(t);
    test_class_DList_swap(t);
    test_class_DList_splice(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs class DList test suite, prints results to cout.
int main()
{
    Tester t;
    test_class_DList(t);

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

