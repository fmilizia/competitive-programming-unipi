# Lecture 17 (19/11/2019)

## Longest increasing subsequence
The problem can be found [here](https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence/0)
and [this](code/lis.cpp) is my code.

The idea, in the style of dynamic programming, is considering subproblems given by:
 - a prefix of the original sequence;
 - a prescribed final number of the subsequence.
 
The easy algorithm that fills the table runs in O(N * MAXA * MAXA), where MAXA is an upper bound on the elements of the sequence.
With the observation that when passing from a row to the next one only an element change, the table can be filled in O(N * MAXA).
The running time is decreased to O(N * log MAXA) if one uses a Fenwick tree capable of computing maximum of prefixes. 

Complexity: O(N * log MAXA) time, O(N + MAXA) space.

## Longest bitonic subsequence
The problem can be found [here](https://practice.geeksforgeeks.org/problems/longest-bitonic-subsequence/0)
and [this](code/bitonic.cpp) is my code.

Compute two arrays:
 - increasing_prefix[0..N-1]. It stores the maximum length of an increasing subsequence of the prefix ending at the ith position.
 - decreasing_suffix[0..N-1]. It stores the maximum length of a decreasing subsequence of the suffix starting at the ith position.
 
The two arrays are computed as in the preceding problem (Longest increasing subsequence).
At the end, the answer is the maximum increasing_prefix[i] + decreasing_suffix[i] - 1, for i = 0..N-1.

One can avoid to actually store the second array, computing the answer on the fly.
Complexity: O(N * log MAXA) time, O(N + MAXA) space.
