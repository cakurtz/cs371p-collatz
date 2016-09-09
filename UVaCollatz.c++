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
// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// ----------------------------

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream


using namespace std;

#define ENABLE_OPTIMIZATION

#ifdef ENABLE_OPTIMIZATION
const int MAX_CYCLE_INPUT = 1000000;

int cycle_cache[MAX_CYCLE_INPUT] = {};
#endif

// ------------
// collatz_read
// ------------

/// Reads the values of an istream.
/** Takes in an istream and inputs the values into a reference of a
    parameterized variable. */

bool collatz_read(istream &r, int &i, int &j) {
  if (!(r >> i))
    return false;
  r >> j;
  return true;
}

// ------------
// collatz_eval
// ------------

/// Computes the max cycle length within the given range.
/** collatz_eval() decides which parameter is the starting point of the range
    and which one is the stopping point. It then computes the cycles for all
    numbers within that range, keeping track of the maximum cycle. A call to
    collatz_calc() computes the cycle length of each number. */

#ifdef ENABLE_OPTIMIZATION
int collatz_eval(int i, int j) {
  int max_cycle;
  int current_cycle;
  int current_comp;
  int start_range;
  int end_range;

  max_cycle = 1;
  int high_range;

  // Error checking to ensure valid number
  if (i <= 0 || i >= MAX_CYCLE_INPUT || j <= 0 || j >= MAX_CYCLE_INPUT)
    throw "Not a valid number!";

  // Checking to see if smaller value is i or j
  if (i < j) {
    high_range = (j / 2) + 1;
    if (i < high_range)
      start_range = high_range;
    else
      start_range = i;
    end_range = j;
  } else {
    high_range = (i / 2) + 1;
    if (j < high_range)
      start_range = high_range;
    else
      start_range = j;
    end_range = i;
  }
  for (current_comp = start_range; current_comp <= end_range; ++current_comp) {
    if (cycle_cache[current_comp] != 0)
      current_cycle = cycle_cache[current_comp];
    else {
      current_cycle = collatz_calc(current_comp);
      cycle_cache[current_comp] = current_cycle;
    }
    if (current_cycle > max_cycle)
      max_cycle = current_cycle;
  }
  return max_cycle;
}

#else
int collatz_eval(int i, int j) {
  int max_cycle;
  int current_cycle;
  int current_comp;
  int start_range;
  int end_range;

  max_cycle = 1;
  if (i < j) {
    start_range = i;
    end_range = j;
  } else {
    start_range = j;
    end_range = i;
  }
  for (current_comp = start_range; current_comp <= end_range; ++current_comp) {
    current_cycle = collatz_calc(current_comp);
    if (current_cycle > max_cycle)
      max_cycle = current_cycle;
  }
  return max_cycle;
}
#endif

// ------------
// collatz_calc
// ------------

/// Calculation of cycle length.
/** collatz_calc() decides whether the parameter is an even or odd number and
    then performs the appropriate calculation. Once the value reaches 1, we
    return the length of the cycle back to collatz_eval() */

// Runs the computation of the cycle length of a given int
int collatz_calc(int comp_cycle) {
  int cycle_length;
  int current_value;

  cycle_length = 1;
  current_value = comp_cycle;
  while (current_value != 1) {
    if ((current_value % 2) == 0)
      current_value = current_value / 2;
    else
      current_value = 3 * current_value + 1;
    ++cycle_length;
  }
  return cycle_length;
}

// -------------
// collatz_print
// -------------

/// Prints the range endpoints and the maximum cycle length.
/** Prints out a string that starts off with the first parameter to
    callatz_eval(), followed by the second, and finally ends with the
    maximum cycle length between the two numbers. */

void collatz_print(ostream &w, int i, int j, int v) {
  w << i << " " << j << " " << v << endl;
}

// -------------
// collatz_solve
// -------------

/// Takes in the values from an input stream and calls eval and print.
/** Takes an istream and parses through it to extract the values used as
    the range endpoints for the computation and calls collatz_eval() to
    compute the results and prints them out to the ostream. */

void collatz_solve(istream &r, ostream &w) {
  int i;
  int j;
  while (collatz_read(r, i, j)) {
    const int v = collatz_eval(i, j);
    collatz_print(w, i, j, v);
  }
}
// -------------------------------
// projects/collatz/RunCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// -------------------------------

// --------
// includes
// --------

#include <iostream> // cin, cout


// ----
// main
// ----

int main() {
  using namespace std;
  collatz_solve(cin, cout);
  return 0;
}
