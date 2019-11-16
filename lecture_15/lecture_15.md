# Lecture 15 (11/11/2019)

## Longest common subsequence
The problem can be found [here](https://practice.geeksforgeeks.org/problems/longest-common-subsequence/0)
and [this](code/lcs.cpp) is my code.

The solution uses a dynamic programming approach.

Let a[0...N-1] and b[0...M-1] be the two strings.

We fill a table T[][] of M+1 columns and N+1 rows, indexed starting from 0.
At the end, T[i][j] will be the lenght of the longest common subsequence of a[0...i-1] and b[0...j-1], and the answer to the problem will be T[N][M].

T[i][j] is computed as the maximum between:
 - T[i-1][j]. This means that we discard the last letter of a[0...i-1].
 - T[i][j-1]. This means that we discard the last letter of b[0...j-1].
 - T[i-1][j-1] + 1, **but only if a[i-1] == b[j-1]**.

Time complexity: O(NM)
Space complexity: O(NM) but it is easily reduced to O(M), because in order to compute the values in row i, only the row i-1 is needed.


## 0-1 Knapsack
The problem can be found [here](https://www.spoj.com/problems/KNAPSACK/)
and [this](code/knapsack.cpp) is my code.

We fill a table T[][] of S+1 columns and N+1 rows, where N is the number of objects and S is the size of the knapsack. 
The rows are indexed from 0 to N, and the columns from 0 to S.
At the end, T[i][c], where 0<=i<=N and 0<=c<=S, will be the maximum sum of values of object chosen among those indexed from 0 to i-1, fitting in the knapsack.

The first row is all zeroes.

The other rows are computed as follows: T[i][c] is the maximum between:
 - T[i-1][c]. This means that we do not choose the last object.
 - T[i-1][c - weight[i-1]] + value[i-1], if c >= weight[i-1]. This means that we choose the last object.

The answer to the problem is T[N][S].

Time complexity: O(NS)
Space complexity: O(NS) but it is easily reduced to O(S), because of this observation: in order to compute the values in row i, only the row i-1 is needed.
