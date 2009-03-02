
#include "ssarray.h"

#include <iostream>
using namespace std;

int main(){
    SSArray<int> ia(10);    // array of 10 int's
    SSArray<double> da(20); // array of 20 double's
//    SSArray<int> iax;       // WILL NOT COMPILE; SSArray has no default ctor
//    SSArray x(10);          // WILL NOT COMPILE; no template parameter

    // Set all items (counter loop)
    for (int c = 0; c < ia.size(); ++c)
    {
        ia[c] = c * c;
    }

    // Print all items (iterator loop)
    int * iter;
    for (iter = ia.begin(); iter != ia.end(); ++iter)
    {
        cout << "Item :" << *iter << endl;
    }

    const SSArray<int> ia2 = ia;  // Copy constructor
    if (ia2 == ia)               // Condition should be true
        cout << "Equal!" << endl;

    SSArray<double> da2(10);
    da2 = da;                // Copy assignment
//    da2 = ia;                // WILL NOT COMPILE; different types

    if (da == ia)            // WILL NOT COMPILE; different types
       cout << "ZZZ" << endl;

return 0;
}
