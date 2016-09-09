// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------

#ifndef Collatz_h
#define Collatz_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair

using namespace std;

/** \mainpage My Implementation of Collatz
*
* \section implementation_sec Implementation
*
* My implementation of collatz is broken up into two functions. The first,
*collatz_eval(), determines the range of all the cycle lengths that need to be
*computed to find the max cycle length in that particular range. It does this by
*figuring out which of the two parameters is larger and sets that as the
*endpoint. The second function, collatz_calc(), is a helper function developed
*to increase readability. All that funtion does is determines whether the one
*int passed to it is even or odd and performs the appropriate calculation and
*repeats until it gets down to 1 and tracks of the cycle length.
*
* \section optimization_sec Optimization
*
* My optimizations include a lazy cache along with a formula that takes the
*higher value of the two ints passed into collatz_eval() and divides it by 2 and
*add 1. If this number is larger than the smaller value, we use this one as the
*starting point because we know that any number above this point up until the
*ending point will have a longer cycle length than anything below it. This is
*due to the fact that all the numbers in this new range will at some point get
*to the numbers we are cutting out and therefore, will result in a higher
*maximum cycle length.
*/

// ------------
// collatz_read
// ------------

/**
 * read two ints from r into i an j
 * @param r an istream
 * @param i an int
 * @param j an int
 * @return true if the read is successful, otherwise false
 */
bool collatz_read(istream &r, int &i, int &j);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int collatz_eval(int i, int j);

// ------------
// collatz_calc
// ------------

/**
 * calculates the cycle length of the given value
 * @param comp_cycle the number to compute the cycle length for
 * @return the cycle length of comp_cycle
 */
int collatz_calc(int comp_cycle);

// -------------
// collatz_print
// -------------

/**
 * print three ints to w
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void collatz_print(ostream &w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void collatz_solve(istream &r, ostream &w);

#endif // Collatz_h
