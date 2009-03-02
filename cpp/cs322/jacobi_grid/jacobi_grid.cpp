// jacobi_grid.h
//
// Amiel Martin
// November 14, 2008
//
// This is program 2 for CSCI 322 Fall quarter, 2008 with Meehan
// 
// JacobiGrid is an object that encapsulates the grid itself
// with the jacobi (average) calculation used for this project


#include "jacobi_grid.h"

#include <cmath> // for fabs

// macros for iterating over the grid
// they use data members +size_y_+ and +size_x_+
// and provide +row+ and +column+
#define iterate_entire_grid_rows for(size_t row=0; row < size_y_; ++row)
#define iterate_entire_grid_columns for(size_t column=0; column < size_x_; ++column)

#define iterate_inner_grid_rows for(size_t row=1; row < size_y_ - 1; ++row)
#define iterate_inner_grid_columns for(size_t column=1; column < size_x_ - 1; ++column)

/*
 * prints the grid to out to out
 */
void JacobiGrid::print(ostream & out) const {
	iterate_entire_grid_rows {
		iterate_entire_grid_columns {
			out << grid_[row][column] << ' ';
		}
		out << std::endl;
	}
}

/*
 * load the entire grid
 * pre: grid_ size has been established
 * post: grid_ has been filled with data from istream in
 */
void JacobiGrid::load(istream & in) {
	float tmp;
	iterate_entire_grid_rows {
		iterate_entire_grid_columns {
			in >> tmp;
			grid_[row][column] = tmp;
		}
	}
}

// throws std::range_error, with description including +caller+ unless y is within the calculatable rows range
void JacobiGrid::throw_unless_row_in_range(size_t y, string caller) const {
	if (y >= size_y_ - 1 || y <= 0 )
		throw std::range_error("in " + caller + ": row out of range");
}

// calculate the average
// returns the difference between the new and old values
// pre: row and column must be within the inner grid
// post: item at row, column in this grid_ is set as the average of points around it from the +other+ grid
float JacobiGrid::calculate_item(int row, int column, JacobiGrid* other) {
	grid_[row][column] = (other->grid_[row-1][column] + other->grid_[row+1][column] + other->grid_[row][column-1] + other->grid_[row][column+1]) / 4;
	return fabs(grid_[row][column] - other->grid_[row][column]);
}

// run the jacobi iteration for just one row
float JacobiGrid::calculate_row(int row, JacobiGrid* other) {
	throw_unless_row_in_range(row, "JacobiGrid::calculate_row(int)");
	
	float max_change = 0;
	
	iterate_inner_grid_columns {
		float tmp = calculate_item(row, column, other);
		max_change = std::max(max_change, tmp);
	}
	
	return max_change;
}

