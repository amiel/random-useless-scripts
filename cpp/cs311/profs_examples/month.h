// month.h
// Glenn G. Chappell
// 11 Sep 2006
//
// For CS 311
// Header for class Month
// Example of simple class with operators

#ifndef FILE_MONTH_H_INCLUDED
#define FILE_MONTH_H_INCLUDED

#include <iosfwd>  // for std::ostream (used only in declarations)
#include <string>  // for std::string

// ************************************************************************
// class Month - Definition
// ************************************************************************

// class Month
// Stores a month/year pair.
// Invariants:
//     month_ is in [1,12]
class Month {

// ***** Month: Ctors, dctor, op= *****
public:

    // Default ctor
    // Pre: None.
    // Post:
    //     month_ == 1
    //     year_ == 1970
    Month()
        :month_(1),
         year_(1970)
    {}

    // Ctor from data
    // Pre: None.
    // Post:
    //     if theMonth is legal (in [1,12]) then month_ == theMonth
    //      otherwise, month_ == 1.
    //     year_ == theYear
    Month(int theMonth,
          int theYear)
        :month_(),
         year_(theYear)
    {
        setMonth(theMonth);  // for bad-value check
    }

    // Compiler-generated copy ctor, copy assignment, dctor are used.

// ***** Month: General public functions *****
public:

    // getMonth
    // Returns the month number (1-12)
    // Pre: None.
    // Post:
    //     return == month_
    int getMonth() const
    { return month_; }

    // getYear
    // Returns the year number
    // Pre: None.
    // Post:
    //     return == year_
    int getYear() const
    { return year_; }

    // setMonth
    // Sets month number
    // Pre: None.
    // Post:
    //     if theMonth is legal (in [1,12]) then month_ == theMonth
    //      otherwise, month_ == 1.
    void setMonth(int theMonth)
    {
        month_ = theMonth;
        if (month_ < 1 || month_ > 12)
            month_ = 1;
    }

    // setYear
    // Set year number
    // Pre: None.
    // Post:
    //     year_ == theYear
    void setYear(int theYear)
    { year_ = theYear; }

// ***** Month: Operators *****
public:

    // operator++ (pre-increment)
    // Goes to the next month (12/1980 goes to 1/1981)
    // Pre: None.
    // Post:
    //     Month/year is the month and year of the next month.
    //     Return is reference to self.
    Month & operator++();

    // operator++ (post-increment)
    // Goes to the next month (12/1980 goes to 1/1981)
    // Pre: None.
    // Post:
    //     Month/year is the month and year of the next month.
    //     Return is old value of self.
    Month operator++(int);

    // operator-- (pre-decrement)
    // Goes to the previous month (1/1980 goes to 12/1979)
    // Pre: None.
    // Post:
    //     Month/year is the month and year of the previous month.
    //     Return is reference to self.
    Month & operator--();

    // operator-- (post-decrement)
    // Goes to the previous month (1/1980 goes to 12/1979)
    // Pre: None.
    // Post:
    //     Month/year is the month and year of the previous month.
    //     Return is old value of self.
    Month operator--(int);

// ***** Month: Data members *****
private:

    int month_;  // Month. 1 = Jan, 2 = Feb, etc.
    int year_;   // Year. 1970 is stored as 1970, not 70.

};  // End class Month

// ************************************************************************
// class Month - Declarations of associated global operators
// ************************************************************************

// operator<< (stream insertion)
// Prints a Month, as month/year, no padding with spaces/zeroes.
// For example, "3/2006".
// Pre: None.
// Post:
//     Month is printed, as above, to the given stream.
std::ostream & operator<<(std::ostream & theStream,
                          const Month & theMonth);

// operator== (equality test)
// Checks equality of two Month's.
// Month's are equal if both months and years are equal.
// Pre: None.
// Post:
//     Returns true if month_ members are equal for a, b
//      and year_ members are equal for a, b.
//     Returns false otherwise.
bool operator==(const Month & a,
                const Month & b);

// operator!= (inequality test)
// Checks inequality of two Month's.
// Month's are equal if both months and years are equal.
// Pre: None.
// Post:
//     Returns !(a == b)
bool operator!=(const Month & a,
                const Month & b);

#endif //#ifndef FILE_MONTH_H_INCLUDED
