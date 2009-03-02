// allocate2.cpp
// Glenn G. Chappell
// 22 Sep 2006
//
// For CS 311
// Source for function allocate2
// Demonstration of error signaling using an exception
//
// THIS IS NOT A COMPLETE PROGRAM!

// allocate2
// Given the size of two arrays to allocate, attempts to
// allocate a dynamic array of int's and a dynamic array of
// double's both of the given size, and returns pointers to
// these in iptr, dptr, respectively. Old values of iptr,
// dptr are discarded. Throws std::bad_alloc if either
// allocation is unseuccessful.
// Pre:
//     size >= 0
// Post:
//     iptr points to array of size int's, allocated with
//      new [], ownership transfered to caller.
//     dptr points to array of size double's, allocated with
//      new [], ownership transfered to client.
// May throw std::bad_alloc.
void allocate2(size_t size,
               int * & iptr,
               double * & dptr)
{
    iptr = new int[size];
    // If the 1st allocation fails, the "new" throws, and we
    // leave. No clean-up necessary.

    try
    {
        dptr = new double[size];
        // If the 2nd allocation fails, we need to clean up
        // the first.
    }
    catch (...)
    {
        delete [] iptr;
        throw;
    }
}
