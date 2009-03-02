// dlist.h (UNFINISHED)
// Glenn G. Chappell
// 11 Nov 2006
//
// For CS 311
// Header for DList class:
//  Doubly Linked List

#ifndef FILE_DLIST_H_INCLUDED
#define FILE_DLIST_H_INCLUDED

// ************************************************************************
// class DList - Class definition
// ************************************************************************

// class DList
// Doubly Linked List
class DList {

// ***** DList: types & constants *****
public:

    typedef int value_type;         // type of items in the list
    typedef std::size_t size_type;  // type of size of a list

    // Node class
    class Node {

    // ***** DList::Node: types *****
    public:

        typedef DList::value_type value_type;

    // ***** DList::Node: ctor(s), dctor *****
    private:

        Node(const value_type & theItem,
             Node * theNext,
             Node * thePrev)
            :item_(theItem),
             next_(theNext),
             prev_(thePrev)
        {}

        ~Node()
        { delete next_; }

    // ***** DList::Node: public functions *****
    public:

        // item (non-const & const)
        value_type & item()
        { return item_; }
        const value_type & item() const
        { return item_; }

        // next (non-const & const)
        Node * next()
        { return next_; }
        const Node * next() const
        { return next_; }

        // prev

    // ***** DList::Node: data members *****
    private:

        value_type item_;
        Node * next_;
        Node * prev_;

    };  // end class DList::Node

    typedef ??? iterator;  // "iterator" types
    typedef ??? const_iterator;

// ***** DList: ctors, dctor, op= *****
public:

    // default ctor

    // copy ctor

    // copy assignment

    // dctor

// ***** DList: general public functions *****
public:

    // empty

    // size

    // begin

    // end

    // swap

    // insert

    // del

    // splice

// ***** DList: Data members *****
private:

    ???

};  // end class DList

#endif //#ifndef FILE_DLIST_H_INCLUDED