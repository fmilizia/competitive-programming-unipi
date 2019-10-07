# Lecture 6 (01/10/2019)

## Ilya and queries
The problem can be found [here](http://codeforces.com/problemset/problem/313/B?locale=en)
and [this](code/ilya-and-queries.cpp) is my code.

Compute the prefix sums of the array of 0 and 1, 1 corresponding to indices i such that the i-th character is equal to the next one.
It is computed in linear time; after that each query takes constant time.

## Alice, Bob and chocolate
The problem can be found [here](http://codeforces.com/problemset/problem/6/C?locale=en)
and [this](code/chocolate.cpp) is my code.

The solution is a simulation of the actions of Alice and Bob.
It takes linear time.

## Number of ways
The problem can be found [here](http://codeforces.com/problemset/problem/466/C?locale=en)
and [this](code/number-of-ways.cpp) is my code.

Once we compute the sum of the elements of the array, we know that each of the segments
we split the array into must have sum equal to S = one third the total sum.

If the total sum is not a multiple of 3, then there is no good subdivision.
Otherwise, start reading the array from the left. Every time we pass through a point in which 
the sum of the elements on its left is equal to S, increment a counter by one.
If the sum is equal to 2S, add the value of the counter to the answer.

The algorithm runs in linear time and constant additional space.

## Little girl and maximum sum
The problem can be found [here](http://codeforces.com/problemset/problem/276/C?locale=en)
and [this](code/max-sum.cpp) is my code.

The main part of the problem is computing, for each position, the number of times it is included in a query.
After that it is enough to put the smaller numbers in the less frequent positions, and this is easily done via a sorting algorithm.

Starting from an array with entries equal to 0,
for each query add a +1 in the left extreme of the interval and a -1 just after the end.
Finally, compute the prefix sum of the array.

Complexity: linear.
