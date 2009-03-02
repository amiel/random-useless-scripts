// memowrapper.h
// Amiel Martin
// Dec  4 2006

// Memoizing wrapper class
// for cs311 - assignment # 9


#ifndef MEMOWRAPPER_H
#define MEMOWRAPPER_H

#include <map> // for std::map

// class MemoWrapper
// requirements on types:
// 	InType has op<
//	InType and OutType have copy ctors
// class invariants:
//	func_ points to a deterministic function (see explination for MemoWrapper(OutType (*)(const InType&)); )
//	c_ contains arg/return value pairs corresponding to calls to func_
template <typename InType, typename OutType>
class MemoWrapper {

  // *** 1-parm ctor, and big three ***
  public:

    // 1-parm ctor
    // Strong Guarantee
    // throws anything that funcS copy ctor could throw
    // pre:
    //	theFunc must be deterministic; its value depends only on its input (the key).
    //	     Using the same input multiple times results in the same output each time.
    //		(thanks Glenn Chappell for this explanation)
    //	theFunc has op() or actually is a function
    // post: class is initialized
    MemoWrapper(OutType (*theFunc)(const InType&)) : func_(theFunc) { }

    // *** use silently written big three ***

   // *** operators ***
  public:

    // operator ()
    // Basic Guarantee
    // throws anything that func could throw
    // throws anything that InType or OutTypeS copy ctor could throw
    // pre: none
    // post: returns the result that calling func_(arg) returns
    //	NOTE: this result is cached
    OutType operator () (InType arg) {
      if (c_.find(arg) != c_.end())
	return c_[arg];
      return c_[arg] = func_(arg);
    }
    
  // *** data members ***
  private:
    std::map<InType, OutType> c_; // c for calculated
    OutType (*func_)(const InType&);
};

#endif // #ifndef MEMOWRAPPER_H
