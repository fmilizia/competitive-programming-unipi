# Lecture 18 (25/11/2019)

## Vertex Cover
The problem can be found [here](http://www.spoj.com/problems/PT07X/)
and [this](code/vertex_cover.cpp) is my code.

My solution uses a dynamic programming approach.
There are two subproblems for each node v of the tree:
 - a(v) = the minimum size of a vertex cover of the subtree with root v;
 - b(v) = the minimum size of a vertex cover of the subtree with root v, containing v.
In the implementation, those values are returned as first and second component of a pair of integers.

The recursive relations are:
 - b(v) = 1 + sum{a(u) where u is a child of v}
 - a(v) = min(b(v), sum{b(u) where u is a child of v})
 
Time and space complexity are linear in the number of nodes.

## Longest palindromic subsequence
The problem can be found [here](https://practice.geeksforgeeks.org/problems/longest-palindromic-subsequence/0)
and [this](code/palindromic.cpp) is my code.

My solution uses a dynamic programming approach, with one subproblem for each contiguous substring of the given string.

The answer lps(l,r) for the substring S[l..r] is the maximum among:
 - lps(l+1, r), meaning that we ignore the first element;
 - lps(l, r-1), meaning that we ignore the last element;
 - if S[l] == S[r], lps(l+1, r-1), meaning that we include in the solution the last and the first elements, which are equal.
The final answer is lps(0, n-1) if n is the length of the string S.

I process the subproblems in decreasing l and increasing r. When solving the subproblem with a fixed l, only the results with l+1 are needed. This allows us to decrease the space complexity from O(n^2) to O(n).

Time complexity: O(n^2)
Space complexity: O(n)
