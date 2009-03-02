// jacobi_grid.h
//
// Amiel Martin
// November 14, 2008
//
// This is program 2 for CSCI 322 Fall quarter, 2008 with Meehan
// 
// JacobiGrid is an object that encapsulates the grid itself
// with the jacobi (average) calculation used for this project


#ifndef JACOBI_GRID_H
#define JACOBI_GRID_H

// for JacobiGrid::print
// and JacobiGrid::load
#include <iostream>
using std::istream;
using std::ostream;

#include <cstdlib>
using std::size_t;

#include <vector>

#include <string>
using std::string;

#include <stdexcept>
// using std::range_error

#include <algorithm>
// using std::max

class JacobiGrid {

	/* Grid typedefs */
public: 
		// each row is a list of floats
	typedef std::vector<float> GridRow;

		// a grid is a list of rows
	typedef std::vector<GridRow> Grid;

	// *** JacobiGrid: ctors, op=, dctor *** //
public:
	// no default ctor, we need sizes

	// ctor
	// Pre: size_x and size_y must be reasonable ( > 0 )
	// Post: sizes are set and we start with an empty grid of 0's (we'll initialize values later)
	JacobiGrid(size_t size_x, size_t size_y)
		: size_x_(size_x), size_y_(size_y), grid_(size_y, GridRow(size_x, 0))
		{ }

	// use default dctor
	// use default op= and copy ctor

public:
    // print
    // Pre: none
    // Post: ostream out has a nice visual representation of board_ printed to it
    void print(ostream & out) const;


	// load the entire grid
	// pre: grid_ size has been established
	// post: grid_ has been filled with data from istream in
	void load(istream & in);

	// number_of_calculatable_rows returns the number of rows without the boundry rows,
	// because boundry rows are not calculated
	size_t number_of_calculatable_rows() { return size_y_ - 2; }
	
	// run the jacobi iteration for just one row
	float calculate_row(int, JacobiGrid*);
	
private:
	float calculate_item(int, int, JacobiGrid*);
	
	// throws std::range_error, with description including +caller+ unless y is within the calculatable rows range
	void throw_unless_row_in_range(size_t y, string) const;

// *** JacobiGrid: Data Members *** //
private:
	const size_t size_x_; // width of grid,    > 0
	const size_t size_y_; // height of grid,   > 0
	Grid grid_; // 2D vector, must be size_x_ by size_y_

};

#endif