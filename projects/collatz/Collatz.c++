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

// ------------
// collatz_read
// ------------

bool collatz_read (istream& r, int& i, int& j) {
    if (!(r >> i))
        return false;
    r >> j;
    return true;}

// ------------
// collatz_eval
// ------------

int collatz_eval (int i, int j) {
    int max_cycle;
    int current_cycle;
    int current_comp;
    int start_range;
    int end_range;

    max_cycle = 1;
    if (i < j) {
        start_range = i;
        end_range = j;
    }
    else {
        start_range = j;
        end_range = i;
    }
    for(current_comp = start_range; current_comp <= end_range; ++current_comp) {
        current_cycle = collatz_calc (current_comp);
        if (current_cycle > max_cycle)
            max_cycle = current_cycle;
    }
    return max_cycle;}

// ------------
// collatz_calc
// ------------

int collatz_calc (int comp_cycle) {
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

void collatz_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// collatz_solve
// -------------

void collatz_solve (istream& r, ostream& w) {
    int i;
    int j;
    while (collatz_read(r, i, j)) {
        const int v = collatz_eval(i, j);
        collatz_print(w, i, j, v);}}
