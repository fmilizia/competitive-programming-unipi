# Lecture 16 (12/11/2019)

## Subset sum
The problem can be found [here](https://practice.geeksforgeeks.org/problems/subset-sum-problem/0)
and [this](code/subset_sum.cpp) is my code.

The solution uses a dynamic programming approach.

First of all check if the sum of the elements of the array is even. If it is, then we must look for a subset of sum equal to half the total sum.
Otherwise the answer is NO.

Let S be half of the total sum.

We fill a table T[][] of S+1 columns and N+1 rows, where N is the length of the array. 
The rows are indexed from 0 to N.
At the end, T[i][c], where 0<=i<=N and 0<=c<=S, will be true if it is possible to choose a subset of the first i elements with sum c, and false otherwise.

The first row is: T[0][0] = true, T[0][c] = false for c > 0.

The other rows are computed as follows: T[i][c] is true if one of the following is true:
 - T[i-1][c]
 - T[i-1][c - arr[i-1]]

The answer to the problem is T[N][S].

Time complexity: O(NS)
Space complexity: O(NS) but it is easily reduced to O(S), because of this observation: in order to compute the values in row i, only the row i-1 is needed.


## Minimum number of jumps
The problem can be found [here](https://practice.geeksforgeeks.org/problems/minimum-number-of-jumps/0)
and [this](code/jumps.cpp) is my code.

The following solution has linear complexity.

Let A[0...N-1] the array given in input.
The first step is to compute a list of "useful position", that are positions i such that i+A[i] > j+A[j] for every j < i.
In fact, one can show that there is always an optimal solution that only uses these useful positions.
Now the strategy is simple: starting from position 0 (which is always useful by definition), always jump to the further possible useful position.


## Edit distance
The problem can be found [here](https://practice.geeksforgeeks.org/problems/edit-distance/0)
and [this](code/edit_dist.cpp) is my code.

The solution uses a dynamic programming approach.

Let a[0...N-1] and b[0...M-1] be the two strings.

We fill a table T[][] of M+1 columns and N+1 rows, indexed starting from 0.
At the end, T[i][j] will be the edit distance between a[0...i-1] and b[0...j-1], and the answer to the problem will be T[N][M].

T[i][j] is computed as the minimum between:
 - T[i-1][j]. This means that we delete the last letter of a[0...i-1].
 - T[i][j-1]. This means that we append a letter to a[0...i-1] equal to b[j-1].
 - T[i-1][j-1] + 1. This means that we change the last letter of a[0...i-1], making it equal to b[j-1].
 - T[i-1][j-1], **but only if a[i-1] == b[j-1]**. It is the same case as the preceding one, but we do not need to change the letter.

Time complexity: O(NM)
Space complexity: O(NM) but it is easily reduced to O(M), because in order to compute the values in row i, only the row i-1 is needed.
