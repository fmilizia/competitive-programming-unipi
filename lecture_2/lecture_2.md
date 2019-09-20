# Lecture 2 (17/09/2019)

## Next larger element
The problem can be found [here](http://practice.geeksforgeeks.org/problems/next-larger-element/0)
and [this](code/next-larger-element.cpp) is my code.

Quite similar to the sliding window maximum problem from lecture 1.
Differences: scan the array from right to left; there is no need to remove ''too old'' elements from the structure (which was a deque for the window problem); 
the answer at a certain position is the most recent element, not the biggest.

All the operations involve the same end of the data structure, hence a vector can be used instead of a deque.

Time: O(N); additional space: O(N).

## Towers
The problem can be found [here](http://codeforces.com/problemset/problem/37/A?locale=en)
and [this](code/towers.cpp) is my code.

Since the size of the bars are integers not greater than 1000, I simply used an array to count how many times every integer occoured in the sequence.

Time: O(N); additional space: O(M) where M is the upper bound for the elements of the array.

## Finding team member
The problem can be found [here](http://codeforces.com/problemset/problem/579/B?locale=en)
and [this](code/finding_team_member.cpp) is my code.

Sort the pairs in increasing order of strength. This is done in O(n^2 log n) and is the most expensive part of the algorithm.
Then read the pairs starting from the strongest: if its components are both free, include that pair in the solution; go on otherwise.
