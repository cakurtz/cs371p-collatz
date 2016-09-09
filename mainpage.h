/**
\mainpage The mainpage documentation

My implementation of collatz is broken up into two functions. The first, collatz_eval(), determines the range of all the cycle lengths that need to be computed to find the max cycle length in that particular range. It does this by figuring out which of the two parameters is larger and sets that as the endpoint. The second function, collatz_calc(), is a helper function developed to increase readability. All that funtion does is determines whether the one int passed to it is even or odd and performs the appropriate calculation and repeats until it gets down to 1 and tracks of the cycle length.

My optimizations include a lazy cache along with a formula that takes the higher value of the two ints passed into collatz_eval() and divides it by 2 and add 1. If this number is larger than the smaller value, we use this one as the starting point because we know that any number above this point up until the ending point will have a longer cycle length than anything below it. This is due to the fact that all the numbers in this new range will at some point get to the numbers we are cutting out and therefore, will result in a higher maximum cycle length.
*/
