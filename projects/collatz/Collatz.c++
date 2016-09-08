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

#include "Collatz.h"

using namespace std;

#define ENABLE_OPTIMIZATION

#ifdef ENABLE_OPTIMIZATION
int cycle_cache[1000000];
#endif

// ------------
// collatz_read
// ------------

bool collatz_read(istream &r, int &i, int &j) {
  if (!(r >> i))
    return false;
  r >> j;
  return true;
}

// ------------
// collatz_eval
// ------------
#ifdef ENABLE_OPTIMIZATION
int collatz_eval(int i, int j) {
  int max_cycle;
  int current_cycle;
  int current_comp;
  int start_range;
  int end_range;

  max_cycle = 1;
  int high_range;

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

void collatz_print(ostream &w, int i, int j, int v) {
  w << i << " " << j << " " << v << endl;
}

// -------------
// collatz_solve
// -------------

void collatz_solve(istream &r, ostream &w) {
  int i;
  int j;
  while (collatz_read(r, i, j)) {
    const int v = collatz_eval(i, j);
    collatz_print(w, i, j, v);
  }
}
