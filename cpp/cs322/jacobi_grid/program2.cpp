// program2.cpp
//
// Amiel Martin
// November 14, 2008
//
// This is program 2 for CSCI 322 Fall quarter, 2008 with Meehan
// 
// == Input
//
// this program expects two parameters and a range of input from standard input
//
// === Arguments
//
// the first argument is the number of threads to create <- int
// the second argument is the convergence value <- float
// 		the program will stop when none of the calculations changes a value by more than the convergence value
// this program does some basic validation on arguments
//
// === Standard Input
//
// The first line should be two integers x and y denoting the size of the problem.
// The remaining lines should be the data to fill the grid.
// this program does not validate input from standard input, 
// it assumes that x and y correctly identify the form of the data that follows



#ifndef DEBUG
#define DEBUG false
#endif


#include <iostream>
using std::cout;
using std::cerr;
using std::cin;
using std::endl;

#include "jacobi_grid.h"
#include "jacobi_thread_group.h"

// help, a simple function to display usage information and an example
void help(char* argv0){
	cerr	<< "Usage:  " << argv0 << " <number of threads> <convergence>" << endl
			<< "Example:" << endl
			<< "\t" << argv0 << " 5 0.01" << endl
		;
}


int main(int argc, char** argv){
	
	/*
	 * parse arguments
	 */
	
	if (argc != 3) {
		help(argv[0]);
		return 1;
	}
	
	int n_threads = atoi(argv[1]);
	float convergence = atof(argv[2]);
	
	if (n_threads <= 0 || convergence <= 0) {
		help(argv[0]);
		cerr << "Error: both <number of threads> and <convergence> should be numbers greater than 0" << endl;
		return 1;
	}
	
	if (DEBUG)
		cout << "got args: n_threads("<<n_threads<<") convergence("<<convergence<<")" << endl;
	
	
	/*
	 * initialize grid
	 */
	
	int x, y;
	// read the size of the grid
	cin >> y >> x;
	
	if (n_threads > y-2) {
		help(argv[0]);
		cerr << "Error: <number of threads> should not be greater than the number of rows" << endl;
		cerr << "\t(n_threads="<<n_threads<<" and rows="<<y<<")" << endl;
		return 1;
	}
	
	// initialize two grids for us to work with from stdin
	JacobiGrid grid1(x, y);
	grid1.load(cin);
	JacobiGrid grid2(grid1);
	
	// pointers will be easier for us to pass around and share between threads
	JacobiGrid* from = &grid1;
	JacobiGrid* to = &grid2;
	
	
	/*
	 * set up thread group and run them
	 */
	
	JacobiThreadGroup threads(n_threads, grid2.number_of_calculatable_rows());
	
	if (DEBUG)
		threads.print_row_range(cout);
		
	to = threads.run_threads(from, to, convergence);	
	
	cout << endl << endl << "convergence has happened: here is the grid" << endl;
	to->print(cout);
	
	return 0;
}

