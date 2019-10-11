# Lectures 7 and 8 (7 and 8/10/2019)

## Megacity
The problem can be found [here](http://codeforces.com/problemset/problem/424/B?locale=en)
and [this](code/megacity.cpp) is my code.

Sort the locations from the nearest to the furthest from the origin;
then add the populations in that order, until 1000000 is reached.

The complexity is that of sorting: O(n log n).


## Find pair
The problem can be found [here](http://codeforces.com/problemset/problem/160/C?locale=en)
and [this](code/find_pair.cpp) is my code.

Just for more clarity, suppose the array of values is indexed from 0 to n-1, and k is between 0 and n^2-1.
Compute a = k / n.
Then, if the array of values is sorted, the first element of the pair we want to find must be the one in position a; let's call it x.
Instead of sorting we can use a faster selection algorithm (like nth_element in the STL).

Count how many elements are strictly smaller than x (cnt_less), and count how many elements are equal to x (cnt_equal).
Then it is not hard to show that the second element of the pair must be the one in position b (if the array is sorted) where
b = (k - cnt_less * n) / cnt_equal.

Complexity: linear + complexity of the selection algorithm, which is linear in average.

## Two heaps
The problem can be found [here](http://codeforces.com/problemset/problem/353/B?locale=en)
and [this](code/two_heaps.cpp) is my code.

There are two kinds of elements: those occouring only once and those occouring multiple times.
To obtain an optimal solution one must distribute the "unique" elements as equally as possible between the two heaps,
and put at least one copy of the "multiple" elements in each heap.

Complexity: linear.
