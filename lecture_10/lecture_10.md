# Lecture 10 (15/10/2019)

## Nested segments
The problem can be found [here](http://codeforces.com/problemset/problem/652/D?locale=en)
and [this](code/nested_segments.cpp) is my code.

Sort the intervals in increasing order of right extreme. This takes O(n log n) time.
Then process the intervals in the obtained order.

Keep a Fenwick tree on top of the array containing a +1 in each position corresponding to 
the left extreme of an already processed interval (and 0 in the other positions).
Then every time you have to process a new interval, first of all find the answer for that interval
counting how many already processed intervals have a left extreme which come after the current left extreme, using the Fenwick tree.
These intervals are exactly those contained in the current one, because we are processing the intervals in increasing 
order of the right extreme.
Then add the left extreme of the current interval to the Fenwick tree.

There is a small subletly: it is necessary to compress the coordinates of the left extremes (those we are using as positions in
the Fenwick tree) before the processing. This is done in O(n log n) time.

Complexity: O(n log n) in time, O(n) in space.


## Pashmak and Parmida's problem
The problem can be found [here](http://codeforces.com/problemset/problem/459/D?locale=en)
and [this](code/pashmak.cpp) is my code.

The solution is divided in two parts.
In the first part the values of f(1, i, a_i) and f(i, n, a_j) are computed for each index i.
These values are stored in two arrays called equal_left and equal_right.
The computation makes use of a sorting algorithm and runs in O(n log n).

In the second part the answer, which is the number of pairs of indices (j,i) with j<i such that equal_left[j] > equal_right[i],
is computed.
The computation makes use of a Fenwick tree built on top of an array which has in position p the number of indices such that equal_left[i] = p.

Complexity: time is O(n log n), space is O(n).
