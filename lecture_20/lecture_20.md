# Lecture 19 (02/12/2019)

## Lexicographically maximum subsequence
The problem can be found [here](http://codeforces.com/problemset/problem/196/A?locale=en)
and [this](code/lms.cpp) is my code.

Start from the last letter in the string, including it in the subsequence.
Then, proceeding backwards, include a letter in the answer if and only if it is not smaller than the already included letters.

This is a simple greedy algorithm which runs in linear time and space.

## Woodcutters
The problem can be found [here](http://codeforces.com/contest/545/problem/C?locale=en)
and [this](code/woodcutters.cpp) is my code.

Going from left to right, try to fell the tree on the left; if this is not possible, try to fell it on the right; if this is not possible, go to the next tree and repeat the same procedure.

Complexity: linear time and space.

## Queue
The problem can be found [here](http://codeforces.com/problemset/problem/141/C?locale=en)
and [this](code/queue.cpp) is my code.

Sort people by **a** value. Of course, if one of these values is **n** or greater, then it is impossible to reconstruct the queue.
We will try to put people in the line by increasing value of **a**. What we need to do is to determine the heights of people.

The idea is similar to insertion sort. Start with an empty list of people. At the end the list will contain everyone and we will assign height **H** to the person in position **N-H** in the list. That is, a person near to the beginning of the list will be taller than a person near to the end.

We insert people in the list by increasing **a**. When we want to insert a person, we have to place it in a very precise position, in such a way that it is preceeded by exactly **a** people in the list. If it is not possible to do so, then the situation is impossible, and the algorithm stops.

The algorithm as described above runs in quadratic time and linear space. But it is possible to obtain a O(n log n) time, inserting people in the opposite order (by decreasing **a**) and using a set of *unused* heights.
