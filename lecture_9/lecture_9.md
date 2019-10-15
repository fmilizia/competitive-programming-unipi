# Lecture 9 (14/10/2019)

## Update the array
The problem can be found [here](http://www.spoj.com/problems/UPDATEIT/)
and [this](code/updateit.cpp) is my code.

I implemented a solution with linear complexity (in time and space).

The first step is to compute an "array of differences" while reading the array.
Its elements are differences of consecutive elements of the true array.

It is very easy to update the difference array: at each step I only need two elements,
corresponding to the boundary of the interval.

At the end compute the prefix sum to obtain the true array, so you can easily answer the queries, each in constant time.
