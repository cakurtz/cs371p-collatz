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
bool collatz_read (istream& r, int& i, int& j);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
int collatz_eval (int i, int j);

// ------------
// collatz_calc
// ------------

/**
 * calculates the cycle length of the given value
 * @param comp_cycle the number to compute the cycle length for
 * @return the cycle length of comp_cycle
 */
 int collatz_calc (int comp_cycle);

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
void collatz_print (ostream& w, int i, int j, int v);

// -------------
// collatz_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void collatz_solve (istream& r, ostream& w);

#endif // Collatz_h
