// student-test.cpp
// Glenn G. Chappell
// 10 Sep 2006
//
// For CS 311
// Used in Assignment 1
// Test file for class Student

#include "student.h"  // For class Student
// Include above BEFORE system files, to make sure it works by itself
#include "student.h"  // Double inclusion test

#include <iostream>  // for std::cout, std::endl
#include <string>    // for std::string

#include <sstream>   // for std::ostringstream

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
// Type Checking Functions
// ************************************************************************

// isString
// Group of functions for testing whether value that is convertible to
// std::string is actually a std::string. Returns true for std::string,
// false for char *.
// Pre: None.
// Post:
//     return == true if param is std::string, false if param is char *.
bool isString(const std::string & s)
{ return true; }

bool isString(const char * s)
{ return false; }

// isInt
// Group of functions for testing whether value that is convertible to
// int is actually a int. Returns true for int, false for other
// built-in types.
// Pre: None.
// Post:
//     return == true if param is int, false if param is unsigned int,
//      short, unsigned short, long, unsigned long, char, unsigned char,
//      double, float, bool.
bool isInt(int i)
{ return true; }

bool isInt(unsigned int i)
{ return false; }

bool isInt(short i)
{ return false; }

bool isInt(unsigned short i)
{ return false; }

bool isInt(long i)
{ return false; }

bool isInt(unsigned long i)
{ return false; }

bool isInt(char i)
{ return false; }

bool isInt(unsigned char i)
{ return false; }

bool isInt(double i)
{ return false; }

bool isInt(float i)
{ return false; }

bool isInt(bool i)
{ return false; }

// ************************************************************************
// Test Suite Functions
// ************************************************************************

// test_class_Student_default_ctor
// Test suite for class Student, default ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_Student_default_ctor(Tester & t)
{
    std::cout << "Test Suite: class Student, default ctor" << std::endl;

    std::string s1;  // Holds names
    int id1;         // Holds IDs

    // Default construct const
    const Student stud1;

    // Check default constructed const name
    s1 = stud1.getName();
    t.test(s1 == "", "Default ctor, name");

    // Check default constructed const ID
    id1 = stud1.getID();
    t.test(id1 == 0, "Default ctor, ID");
}

// test_class_Student_get_and_set_functions
// Test suite for class Student, get & set functions
// Pre: None.
// Post:
//     Global allpassed is false if any tests failed;
//      it is unchanged otherwise.
//     Messages have been printed to cout.
void test_class_Student_get_and_set_functions(Tester & t)
{
    std::cout << "Test Suite: class Student, get and set functions" << std::endl;

    std::string s1;  // Holds names
    int id1;         // Holds IDs
    bool typeCheck;  // For type checking functions
    const std::string bigName = " 1234567891123456789212345678931234567894123456789512345678961234567897123456789812345678991234567891 ";
    const int bigID = 10000000;
        // Values for "big value" tests

    Student stud1("A", 1);
    const Student & stud1r(stud1);
    Student stud2("B", 2);

    // setName parameter type
    Student stud0;
    const std::string s2("");
    stud0.setName(s2);  // This only needs to compile

    // Check getName return type non-const
    typeCheck = isString(stud1.getName());
    t.test(typeCheck, "getName return type non-const");

    // Check getName return type const
    typeCheck = isString(stud1r.getName());
    t.test(typeCheck, "getName return type const");

    // Check getID return type non-const
    typeCheck = isInt(stud1.getID());
    t.test(typeCheck, "getID return type non-const");

    // Check getID return type const
    typeCheck = isInt(stud1r.getID());
    t.test(typeCheck, "getID return type const");

    // Check getName #1 non-const
    s1 = stud1.getName();
    t.test(s1 == "A", "getName #1 non-const");

    // Check getName #1 const
    s1 = stud1r.getName();
    t.test(s1 == "A", "getName #1 const");

    // Check getID #1 non-const
    id1 = stud1.getID();
    t.test(id1 == 1, "getID #1 non-const");

    // Check getID #1 const
    id1 = stud1r.getID();
    t.test(id1 == 1, "getID #1 const");

    // Check getName #2
    s1 = stud2.getName();
    t.test(s1 == "B", "getName #2");

    // Check getID #2
    id1 = stud2.getID();
    t.test(id1 == 2, "getID #2");

    // Check setName #1
    stud1.setName("C");
    s1 = stud1.getName();
    t.test(s1 == "C", "setName #1");

    // Check setID #1
    stud1.setID(3);
    id1 = stud1.getID();
    t.test(id1 == 3, "setID #1");

    // Check setName #2 big value
    stud1.setName(bigName);
    s1 = stud1.getName();
    t.test(s1 == bigName, "setName #2 big value");

    // Check setID #2 big value
    stud1.setID(bigID);
    id1 = stud1.getID();
    t.test(id1 == bigID, "setID #2 big value");

    // Recheck getName #2
    s1 = stud2.getName();
    t.test(s1 == "B", "getName #2 recheck");

    // Recheck getID #2
    id1 = stud2.getID();
    t.test(id1 == 2, "getID #2 recheck");
}


// test_class_Student_data_ctor
// Test suite for class Student, ctor from data
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_Student_data_ctor(Tester & t)
{
    std::cout << "Test Suite: class Student, ctor from data" << std::endl;

    std::string s1;  // Holds names
    int id1;         // Holds IDs

    // data ctor param type
    const std::string s2("");
    Student stud0(s2, 0);  // This only needs to compile

    // Construct from data #1
    const Student stud1("John Smith", 31);

    // Check constructed from data #1 name
    s1 = stud1.getName();
    t.test(s1 == "John Smith", "Ctor from data non-const, name");

    // Check constructed from data #1 ID
    id1 = stud1.getID();
    t.test(id1 == 31, "Ctor from data non-const, ID");

    // Construct from data #2 (const)
    const Student stud2("Jane Jones", 26);

    // Check constructed from data #2 name
    s1 = stud2.getName();
    t.test(s1 == "Jane Jones", "Ctor from data const, name");

    // Check constructed from data #2 ID
    id1 = stud2.getID();
    t.test(id1 == 26, "Ctor from data const, ID");
}


// test_class_Student_copy_ctor
// Test suite for class Student, copy ctor
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_Student_copy_ctor(Tester & t)
{
    std::cout << "Test Suite: class Student, copy ctor" << std::endl;

    std::string s1;  // Holds names
    int id1;         // Holds IDs

    // Copy construct
    Student stud1("Fred Johnson", 48);
    const Student & stud1r(stud1);
    const Student stud2(stud1r);

    // Check copy constructed name
    s1 = stud1.getName();
    t.test(s1 == "Fred Johnson", "Copy ctor, name");

    // Check copy constructed ID
    id1 = stud2.getID();
    t.test(id1 == 48, "Copy ctor, ID");

    // Modify original
    stud1.setName("Joe");
    stud1.setID(14);

    // Recheck copy constructed name
    s1 = stud2.getName();
    t.test(s1 == "Fred Johnson", "Recheck Copy ctor, name");

    // Recheck copy constructed ID
    id1 = stud2.getID();
    t.test(id1 == 48, "Recheck Copy ctor, ID");    
}


// test_class_Student_copy_assn
// Test suite for class Student, copy assignment
// Pre: None.
// Post:
//     Pass/fail status of tests have been registered with t.
//     Appropriate have been messages printed to cout.
void test_class_Student_copy_assn(Tester & t)
{
    std::cout << "Test Suite: class Student, copy assignment" << std::endl;

    std::string s1;  // Holds names
    int id1;         // Holds IDs

    // Copy assign
    Student stud1("Joe Q.", 7);
    const Student & stud1r(stud1);
    Student stud2;
    stud2 = stud1r;

    // Check copy assigned name
    s1 = stud2.getName();
    t.test(s1 == "Joe Q.", "Copy assignment, name");

    // Check copy assigned ID
    id1 = stud2.getID();
    t.test(id1 == 7, "Copy assignment, ID");

    // Modify original
    stud1.setName("abc");
    stud1.setID(14000);

    // Recheck copy assigned name
    s1 = stud2.getName();
    t.test(s1 == "Joe Q.", "Recheck copy assignment, name");

    // Recheck copy assigned ID
    id1 = stud2.getID();
    t.test(id1 == 7, "Recheck copy assignment, ID");
}


// test_class_Student_toString
// Test suite for class Student, toString
// Pre: None.
// Post:
//     Global allpassed is false if any tests failed;
//      it is unchanged otherwise.
//     Messages have been printed to cout.
void test_class_Student_toString(Tester & t)
{
    std::cout << "Test Suite: class Student, toString" << std::endl;

    std::string s1;  // Holds output

    // Test #1
    Student stud1("Simon Garfunkel", 2);

    // Check toString #1
    s1 = stud1.toString();
    t.test(s1 == "Simon Garfunkel 2", "toString non-const");

    // Test #2 (const)
    const Student stud2("A. B. Porter", 1000000);

    // Check toString #2
    s1 = stud2.toString();
    t.test(s1 == "A. B. Porter 1000000", "toString const");
}


// test_class_Student_stream_insertion
// Test suite for class Student, stream insertion
// Pre: None.
// Post:
//     Global allpassed is false if any tests failed;
//      it is unchanged otherwise.
//     Messages have been printed to cout.
void test_class_Student_stream_insertion(Tester & t)
{
    std::cout << "Test Suite: class Student, stream insertion" << std::endl;

    std::string s1;  // Holds output

    // Test #1 (non-const)
    Student stud1("X. Y. Z.", 5);

    // Check stream insertion #1 (non-const)
    std::ostringstream os1;
    os1 << stud1;
    s1 = os1.str();
    t.test(s1 == "X. Y. Z. 5", "stream insertion non-const");

    // Test #2 (const)
    const Student stud2("A. B. C.", 2000000); 

    // Check stream insertion #2 (const)
    std::ostringstream os2;
    os2 << stud2;
    s1 = os2.str();
    t.test(s1 == "A. B. C. 2000000", "stream insertion const");
}


// test_class_Student_comparisons
// Test suite for class Student, comparisons
// Pre: None.
// Post:
//     Global allpassed is false if any tests failed;
//      it is unchanged otherwise.
//     Messages have been printed to cout.
void test_class_Student_comparisons(Tester & t)
{
    std::cout << "Test Suite: class Student, comparisons" << std::endl;

    const Student stud1("A.", 1);
    const Student stud2("B.", 2);
    Student stud1copy1(stud1);
    Student stud1copy2(stud1);

    // Check equality of copies
    t.test(stud1 == stud1copy1, "Equality of copies");

    // Check inequality of copies
    t.test(!(stud1 != stud1copy1), "Inequality of copies");

    // Check equality of different names
    // (Also checks param types)
    t.test(!(stud1 == stud2), "Equality of different Students");

    // Check inequality of different names
    // (Also checks param types)
    t.test(stud1 != stud2, "Inequality of different Students");

    // Modify copy #1
    stud1copy1.setName("X.");

    // Check equality of modification of copy (name)
    t.test(!(stud1 == stud1copy1),
          "Equality of modification of copy (name)");

    // Check inequality of modification of copy (name)
    t.test(stud1 != stud1copy1,
          "Inquality of modification of copy (name)");

    // Modify copy #2
    stud1copy2.setID(11);

    // Check equality of modification of copy (ID)
    t.test(!(stud1 == stud1copy2),
          "Equality of modification of copy (ID)");

    // Check inequality of modification of copy (ID)
    t.test(stud1 != stud1copy2,
          "Inequality of modification of copy (ID)");
}


// test_class_Student
// Test suite for class Student
// Uses other test-suite functions
// Pre: None.
// Post:
//    Global allpassed is false if any tests failed;
//     it is unchanged otherwise.
//    Messages have been printed to cout.
void test_class_Student(Tester & t)
{
    // Do all the test suites
    std::cout << "TEST SUITES FOR CLASS Student" << std::endl;
    test_class_Student_default_ctor(t);
    test_class_Student_get_and_set_functions(t);
    test_class_Student_data_ctor(t);
    test_class_Student_copy_ctor(t);
    test_class_Student_copy_assn(t);
    test_class_Student_toString(t);
    test_class_Student_stream_insertion(t);
    test_class_Student_comparisons(t);
}


// ************************************************************************
// Main program
// ************************************************************************


// main
// Runs class Student test suite, prints results to cout.
int main()
{
    Tester t;
    test_class_Student(t);

    std::cout << std::endl;
    if (t.allPassed())
        std::cout << "All tests successful"
                  << std::endl;
    else
        std::cout << "Tests ********** UNSUCCESSFUL **********"
                  << std::endl;
    std::cout << std::endl;
}
