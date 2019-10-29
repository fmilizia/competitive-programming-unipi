# Lecture 13 (28/10/2019)

## Powerful array
The problem can be found [here](http://codeforces.com/contest/86/problem/D)
and [this](code/powerful.cpp) is my code.

This problem is easily solved using the Mo's algorithm.
If the numbers from 1 to n are divided in blocks, each of size S (the last block being possibly smaller),
the number of add/remove operation is less than St + n^2/S, where t is the number of queries.
Instead of setting S equal to the square root of n, which is the strategy we saw in class, I computed S = sqrt(2)n/sqrt(t),
which is the value minimizing the number of operations I mentioned above.
In this way one obtains time complexity O(n sqrt(t) + t log(t)), where t log(t) comes from sorting the queries.

Apart from the array, an additional O(t + C) space is used, where C is the number of colors.


## Tree and queries
The problem can be found [here](http://codeforces.com/contest/375/problem/D)
and [this](code/tree.cpp) is my code.

First of all, I implemented a struct called ColorCounter, which supports the following operations:
 - add one occurrence of a given color (a color is an integer between 1 and C)
 - remove one occurrence of a given color
 - return the number of colors having at least k occurrences.

The implementation uses a Fenwick tree of size N and a vector of size C (N is the size of the tree in the problem, and at every instant the number of occourrences of 
a given color will be at most N, this is why the Fenwick tree has size N).
The running time of the operations are O(log C) for each operation, since they basically reduce to a couple of operations on the Fenwick tree.

Given a ColorCounter, one approach to solve the problem is to reduce it to a problem on a line (using a Euler tour) and then using Mo's algorithm, obtaining
a total time complexity of O((N sqrt(N) + M) log C), where M is the number of queries.

Instead, I implemented a more efficient solution, which makes use of the special structure of the problem (the property I use, at the end, boils down to
this observation: the intervals involved in the queries are either nested or disjoint. But I don't use this explicitly in my algorithm, since I work directly with the tree and
not with its "linearization").

I use an approach very similar to a "merge to the largest" strategy.
First of all, I compute the subtree-size of every vertex.
Then I compute the answers recursively. Suppose we want to solve the problem for the subtree rooted at vertex V.
First of all, I recursively solve the problem on the subtrees rooted at the **light** children of V, clearing the ColorCounter every time.
Then I solve (recursively) the problem on the **heavy** child, but after that I don't clear the ColorCounter. Then I visit again the subtrees rooted
at the light children, and at the end I add the color of V to the ColorCounter. Now the ColorCounter describes the subtree rooted at V, and I compute 
the answers for the queries with vertex V.

Time complexity: O((N log(N) + M) log(C))
Space complexity: O(N + M + C).
