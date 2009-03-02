// jacobi_thread_group.cpp
//
// Amiel Martin
// November 14, 2008
//
// This is program 2 for CSCI 322 Fall quarter, 2008 with Meehan
// 

#include "jacobi_thread_group.h"


#include <algorithm>
// using std::max
// using std::swap


// iterate each thread
// defines +i+
#define each_thread for(unsigned short i = 0; i < nthreads_; ++i)

// ctor
// Pre: nrows must be more than nthreads
// Post:
// 		* calculates thread chunks
// 		* initializes pthread attributes, mutex, and conditions
// 		* initializes vector of threads and other data members
JacobiThreadGroup::JacobiThreadGroup(int nthreads, int nrows) : nthreads_(nthreads), thread_args_(nthreads), threads_(nthreads) {
	calculate_thread_chunks(nrows);
	
	pthread_attr_init(&threads_attr_);
	pthread_attr_setdetachstate(&threads_attr_, PTHREAD_CREATE_JOINABLE);	
	
	pthread_mutex_init(&cond_mutex_, NULL);
	pthread_cond_init(&cond_, NULL);
}

// dctor
// cleans up after ctor (destroys pthread attributes, mutex, and condition variable)
JacobiThreadGroup::~JacobiThreadGroup(){
	pthread_mutex_destroy(&cond_mutex_);
	pthread_cond_destroy(&cond_);
	pthread_attr_destroy(&threads_attr_);
}

// calculates the start and end values for each thread
// attempting to evenly spread the load
void JacobiThreadGroup::calculate_thread_chunks(int nrows) {
	int rows_per_thread = nrows / nthreads_;
	int current = 0;
	 
	// If nthreads_ divides nrows, then every thread takes on the same amout of threads.
	// If not, some threads need to take on an extra.
	// nrows % nthreads_ is the number of threads that take on the extra row,
	// and nthreads_ - (nrows % nthreads_) is the position where we start
	// setting up threads with the extra row.
	int position_to_increment_rows_per_thread = nthreads_ - (nrows % nthreads_);
	
	each_thread {
		
		if (i == position_to_increment_rows_per_thread)
			++rows_per_thread;
		
		thread_args_[i].start = current + 1;
		current += rows_per_thread;
		thread_args_[i].end = current + 1;
	}
}


// This method runs itself under mutual exclution.
// It is also a barrier.
// It stores the greatest change and sets up a barrier.
// The last thread to get to the barrier swaps the grids
// and checks for convergence.
// In the case of convergence, this function should
// return true for every thread.
bool wait_swap_and_test_convergence(JacobiThreadGroup::thread_arg_t* args, float max_change) {
	pthread_mutex_lock(args->shared->cond_mutex);
	if (DEBUG)
		std::cout << "my greatest change was " << max_change << "\t";
	args->shared->greatest_change = std::max(args->shared->greatest_change, max_change);
	
	++args->shared->nwaiting;
	if (args->shared->nwaiting == args->shared->nthreads) {
		if (DEBUG)
			std::cout << "thread#" << args->shared->nwaiting << " swapping and broadcasting" << std::endl;
		
		args->shared->nwaiting = 0;
		
		if (DEBUG) {
			std::cout << "iteration done: " << std::endl;
			// args->shared->to->print(std::cout); // uncomment this line to print the grid after every iteration
		}
		
		// swap the grids, we can use the old original grid as our new grid to calculate to
		std::swap(args->shared->to, args->shared->from);
		++args->shared->iteration_count;
		
		if (args->shared->greatest_change < args->shared->convergence) {
			args->shared->greatest_change = -1; // signal that convergence has been acheived
		} else {
			args->shared->greatest_change = 0;
		}
		
		pthread_cond_broadcast(args->shared->cond);
	} else {
		if (DEBUG)
			std::cout << "thread#" << args->shared->nwaiting << " waiting" << std::endl;
		pthread_cond_wait(args->shared->cond, args->shared->cond_mutex);
	}
	
	pthread_mutex_unlock(args->shared->cond_mutex);
	
	return args->shared->greatest_change < 0;
}

// This is the method that gets invoked by pthreads
// see JacobiThreadGroup::run_threads for a basic explination
// pre: arguments and shared data have been setup (by JacobiThreadGroup::run_threads)
// post: once all threads exit, the grid in shared_data_.from has acheived convergence
void* thread_body(void* input){
	JacobiThreadGroup::thread_arg_t* args = (JacobiThreadGroup::thread_arg_t *) input;	
	float max_change = 0;
	bool converged = false;
	
	while (!converged) {
		
		max_change = 0;
				
		for(int i = args->start; i < args->end; ++i) {
			float tmp = args->shared->to->calculate_row(i, args->shared->from);
			max_change = std::max(max_change, tmp);
		}

		converged = wait_swap_and_test_convergence(args, max_change); // barrier
	}
    
	
	
	pthread_exit(0);
}

// creates nthreads threads
// each thread calculates the jacobi iteration for its rows and waits for the last to finish
// the last thread to finish its section swaps the grids so they can do it all over again
// all threads continue in this fashon until none of them makes a change larger than convergence
// returns a pointer to the grid that has acheived convergence
JacobiGrid* JacobiThreadGroup::run_threads(JacobiGrid* from, JacobiGrid* to, float convergence){
	shared_data_.cond_mutex = &cond_mutex_;
	shared_data_.cond = &cond_;
	shared_data_.nthreads = nthreads_;
	shared_data_.nwaiting = 0;
	shared_data_.greatest_change = 0;
	shared_data_.iteration_count = 0;
	
	shared_data_.from = from;
	shared_data_.to = to;
	shared_data_.convergence = convergence;
	
	each_thread {
		thread_args_[i].shared = &shared_data_;
	    pthread_create(&threads_[i], NULL, thread_body, (void *)&thread_args_[i]);
	}

	each_thread {
	    pthread_join(threads_[i], NULL); // dont need status
	}
	
	if (DEBUG)
		std::cout << "NUMBER OF ITERATIONS: " << shared_data_.iteration_count << std::endl;
	
	return shared_data_.from;
}

// prints the start and end row for each thread (for debugging)
void JacobiThreadGroup::print_row_range(ostream &out) const {
	each_thread {
		out << thread_args_[i].start << '\t' << thread_args_[i].end << std::endl;
	}
}
