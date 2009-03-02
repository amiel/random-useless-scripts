/*
 * student.h
 * Amiel Martin
 * 2006-9-11
 *
 * For CS311
 * Assignment 1
 * Student class header file
 */

#include <string>
using std::string;

#include <iosfwd> // for std::ostream (only for declarations)


#ifndef STUDENT_H
#define STUDENT_H

// student class
//  represent a student by full name, and id
//  class invariants:
//    0 <= id < 2 ^ (sizeof(int) * 8)  --  is this right?
//    name is a std::string
// NOTE: if a negative id is recieved as input, then id_ is set to 0
// id is assumed to be small enough to fit in an int
class Student {

  // ctors, dctor, op=
  public:
    // Default Ctor
    // pre: none
    // post: name_ == "" && id_ == 0
    Student() : name_(""), id_(0) {}

    // Ctor from data
    // pre: none
    // post:
    //  name_ == name,
    //  if id is negative then id_ == 0,
    //  otherwise id_ == id
    Student(string name, int id) : name_(name), id_() {
      setID(id);
    }

    // Silently written copy ctor, op=, and dctor will be fine
    /*
    Student(const Student &);
    Student operator=(const Student &);
    ~Student(){}
    */

  // general public functions
  public:
    // getName
    // returns the name string
    // pre: none
    // post: return == name_
    string getName() const { return name_; }

    // getID
    // returns the id number
    // pre: none
    // post: return == id_
    int getID() const { return id_; }

    // setName
    // sets the name
    // pre: none
    // post: name_ == name
    void setName(string name) { name_ = name; }

    // setID
    // sets the id
    // pre: none
    // post:
    //  if id is negative then id_ == 0,
    //  otherwise, id_ == id 
    void setID(int id);

    // toString
    // returns the students name and id in one string
    // Example: "John Doe 30"
    // pre: none
    // post: return == name_ + " " + id_
    string toString() const;
     
  // data members
  private:
    string name_; // students full name
    int id_; // 0 <= id < 2 ^ (sizeof(int) * 8)  --  is this right?
};


// declarations of associated global functions

// operator << (stream insertion)
// prints a Students name and id as defined in toString()
// Example: "John Doe 30"
// pre: none
// post: Student is printed as above to the stream
std::ostream & operator << (std::ostream&, const Student&);
 
// operator == (equality test)
// checks equality of two Students
// two Students are equal if both ids and names are equal
// pre: none
// post:
//  returns true if a.id_ == a.id
//  and _a.name_ == b.name_
//  returns false otherwise
bool operator == (const Student & a, const Student & b);

// operator =! (inequality test)
// check inequality of two Students
// two Students are equal if both ids and names are equal
// pre: none
// post: returns !(a == b)
bool operator != (const Student & a, const Student & b);


#endif // #ifndef STUDENT_H
