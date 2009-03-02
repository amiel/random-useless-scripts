// jacobi_thread_group.h
//
// Amiel Martin
// November 14, 2008
//
// This is program 2 for CSCI 322 Fall quarter, 2008 with Meehan
// 
// 


#ifndef JACOBI_THREAD_GROUP_H
#define JACOBI_THREAD_GROUP_H

#include <iostream>
#include <pthread.h>
#include "jacobi_grid.h"

class JacobiThreadGroup {

public:
	
	// structure to hold shared data for all threads
	typedef struct {
		JacobiGrid* from;
		JacobiGrid* to;
		pthread_mutex_t* cond_mutex;
		pthread_cond_t* cond;
		unsigned short nthreads;
		unsigned short nwaiting; // number of threads waiting at a barrier
		float greatest_change;
		float convergence;
		unsigned int iteration_count;
	} thread_shared_t;


	// structure to hold the arguments that each thread gets passed
	// includes a pointer to the shared data
	typedef struct {
		int start; // first row number
		int end; // last row number + 1 (ie this.end == next.start)
		thread_shared_t* shared;
	} thread_arg_t;

public:
	
	// no default ctor, we need sizes

	// ctor
	// Pre: nrows must be more than nthreads
	// Post:
	// 		* calculates thread chunks
	// 		* initializes pthread attributes, mutex, and conditions
	// 		* initializes vector of threads and other data members
	JacobiThreadGroup(int nthreads, int nrows);
	
	// dctor
	// cleans up after ctor (destroys pthread attributes, mutex, and condition variable)
	~JacobiThreadGroup();
	
	// use default op= and copy ctor
	
public:
	// for each thread, print_row_range prints the start and end number for each thread
	void print_row_range(std::ostream &out) const;
	
	// creates nthreads threads
	// each thread calculates the jacobi iteration for its rows and waits for the last to finish
	// the last thread to finish its section swaps the grids so they can do it all over again
	// all threads continue in this fashon until none of them makes a change larger than convergence
	// returns a pointer to the grid that has acheived convergence
	JacobiGrid* run_threads(JacobiGrid* from, JacobiGrid* to, float convergence);

private:
	// calculates the start and end values for each thread
	// attempting to evenly spread the load
	void calculate_thread_chunks(int);
	
private:
	unsigned short nthreads_; // number of threads
	std::vector<thread_arg_t> thread_args_; // arguments for each thread, also a pointer to shared_data_
	thread_shared_t shared_data_;
	pthread_attr_t threads_attr_;
	std::vector<pthread_t> threads_;
	
	pthread_mutex_t cond_mutex_;
	pthread_cond_t cond_;
};

#endif