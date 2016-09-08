// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2016
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string

#include "gtest/gtest.h"

#include "Collatz.h"

using namespace std;

// ----
// read
// ----

TEST(CollatzFixture, read) {
  istringstream r("1 10\n");
  int i;
  int j;
  const bool b = collatz_read(r, i, j);
  ASSERT_TRUE(b);
  ASSERT_EQ(1, i);
  ASSERT_EQ(10, j);
}

// ----
// eval
// ----

TEST(CollatzFixture, eval_1) {
  const int v = collatz_eval(1, 10);
  ASSERT_EQ(20, v);
}

TEST(CollatzFixture, eval_2) {
  const int v = collatz_eval(100, 200);
  ASSERT_EQ(125, v);
}

TEST(CollatzFixture, eval_3) {
  const int v = collatz_eval(201, 210);
  ASSERT_EQ(89, v);
}

TEST(CollatzFixture, eval_4) {
  const int v = collatz_eval(900, 1000);
  ASSERT_EQ(174, v);
}

// Repeats the above steps backwards
TEST(CollatzFixture, eval_5) {
  const int v = collatz_eval(10, 1);
  ASSERT_EQ(20, v);
}

TEST(CollatzFixture, eval_6) {
  const int v = collatz_eval(200, 100);
  ASSERT_EQ(125, v);
}

TEST(CollatzFixture, eval_7) {
  const int v = collatz_eval(210, 201);
  ASSERT_EQ(89, v);
}

TEST(CollatzFixture, eval_8) {
  const int v = collatz_eval(1000, 900);
  ASSERT_EQ(174, v);
}

// Repeat of a previous test
TEST(CollatzFixture, eval_9) {
  const int v = collatz_eval(1000, 900);
  ASSERT_EQ(174, v);
}

// Check a nuber that is the start and end of the range
TEST(CollatzFixture, eval_10) {
  const int v = collatz_eval(1750, 1750);
  ASSERT_EQ(30, v);
}

// ----
// calc
// ----

TEST(CollatzFixture, calc) {
  const int v = collatz_calc(500);
  ASSERT_EQ(111, v);
}

TEST(CollatzFixture, calc_2) {
  const int v = collatz_calc(973451);
  ASSERT_EQ(65, v);
}

// -----
// print
// -----

TEST(CollatzFixture, print) {
  ostringstream w;
  collatz_print(w, 1, 10, 20);
  ASSERT_EQ("1 10 20\n", w.str());
}

// -----
// solve
// -----

TEST(CollatzFixture, solve) {
  istringstream r("1 10\n100 200\n201 210\n900 1000\n");
  ostringstream w;
  collatz_solve(r, w);
  ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());
}

TEST(CollatzFixture, solve_2) {
  istringstream r("10 1\n1000 900\n5 29\n87634 87000\n");
  ostringstream w;
  collatz_solve(r, w);
  ASSERT_EQ("10 1 20\n1000 900 174\n5 29 112\n87634 87000 333\n", w.str());
}

TEST(CollatzFixture, solve_3) {
  istringstream r("57 57\n20 20\n8376 83765\n4321 1234\n");
  ostringstream w;
  collatz_solve(r, w);
  ASSERT_EQ("57 57 33\n20 20 8\n8376 83765 351\n4321 1234 238\n", w.str());
}
