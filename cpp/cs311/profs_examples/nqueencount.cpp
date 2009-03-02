// nqueencount.cpp
// Glenn G. Chappell
// 2 Oct 2006
//
// For CS 311
// Count solutions to n-Queens Problem
// Example of Recursive Solution Search

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <vector>  // for std::vector
#include <cmath>   // for std::abs


typedef std::vector<int> Board;  // Type for "board"

// We represent a partial queen placement on a chessboard as a Board
// and an int. The int ("n") gives the size of the board. Thus, n = 8
// means an 8x8 chessboard. The Board is a listing of the queen
// positions on 0 or more columns of the board (at most n columns). There
// is at most one queen per column. Its position is given by a number
// from 0 to n-1, inclusive.
//
// For example, a Board holding 1, 3 and n = 4 means a 4x4 board with
// queens in its first 2 columns. The queen in the 1st column is in
// position 1 (the 2nd square), and the queen in the 2nd column is in
// position 3 (the 4th & last square). This is pictured below:
//
// - - - -
// Q - - -
// - - - -
// - Q - -


// nQueenCount_isValidAddition
// Given a partial board (see above), determine whether the last
//  queen placement is non-attacking.
// Pre:
//     board, except for last queen place, represents a placement
//      of non-attacking queens (see above).
//     myCol >= 0.
// Post:
//     Return value is true if board is a non-attacking arrangement
//      of queens; false otherwise.
bool nQueenCount_isValidAddition(const Board & board)
{
    int myColumn = board.size() - 1;
    if (myColumn < 0)
        return true;
    int myRow = board[myColumn];

    for (int itsColumn = 0; itsColumn < myColumn; ++itsColumn)
    {
        int itsRow = board[itsColumn];

        // vertical attack from existing queen?
        if (myRow == itsRow)
            return false;

        // diagonal attack from existing queen?
        if (std::abs(myRow - itsRow) == myColumn - itsColumn)
            return false;
    }
    return true;
}


// nQueenCount_recurse
// Given a partial board (see above), counts all non-attacking
//  placements on n Queens that use the given queens.
// Recursive.
// Pre:
//     n > 0.
//     board.size() <= n.
//     Each entry of board is in [0 .. n-1].
///    board represents a placement of non-attacking queens (see above).
// Post:
//     Return == number of solutions based on given partial solution
//      (see above).
//     board is in its original state.
int nQueenCount_recurse(Board & board, int n)
{
    // Base case
    if (board.size() == n)
    {
        // A solution!
        return 1;
    }

    // Recursive case

    int total = 0;  // Total # of solutions based on this partial solution

    // Try each position in next row
    for (int newColumn = 0; newColumn < n; ++newColumn)
    {
        board.push_back(newColumn);  // Add new queen
        // If we can add a queen in position newColumn in the next row ...
        if (nQueenCount_isValidAddition(board))
        {
            // ... then do it, and recurse.
            total += nQueenCount_recurse(board, n);  // Recursive call
        }
        board.pop_back();            // Backtrack
    }

    return total;
}


// nQueenCount
// Returns number of solutions to the n-Queens problem for a board of the
//  given size.
// Pre:
//     n > 0.
// Post:
//     Return == number of solutions.
int nQueenCount(int n)
{
    Board emptyBoard;
    return nQueenCount_recurse(emptyBoard, n);
}


// main
int main()
{
    while (true)
    {
        int n;
        cout << "n-Queen Counter" << endl;
        cout << "by Glenn G. Chappell" << endl;
        cout << "For CS 311 Fall 2006" << endl;
        cout << endl;
        cout << "Board size? ";
        cin >> n;
        while (!cin || n <= 0)  // Bad input
        {
            cin.clear();   // Reset cin for re-try of input
            cin.ignore();
            cout << "Try again - Board size? ";
            cin >> n;
        }
        cout << endl;
        cout << "Number of n-Queen Solutions for "
             << n << " x " << n << " board: ";
        cout << nQueenCount(n) << endl;
        cout << endl;
    }
}