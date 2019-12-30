# Lecture 19 (26/11/2019)

## N meetings in one room
The problem can be found [here](http://practice.geeksforgeeks.org/problems/n-meetings-in-one-room/0)
and [this](code/meetings.cpp) is my code.

An optimal solution is obtained greedily taking, in order, the meeting with the earliest finish time among those with a starting time which is big enough 
in order not to overlap with the previous chosen meeting.

Time: O(N log N) because of sorting

Space: O(N)

## Magic numbers
The problem can be found [here](http://codeforces.com/problemset/problem/320/A?locale=en)
and [this](code/magic.cpp) is my code.

It is enough to chech that the string of digits only contains 1 and 4 and that if,
while reading the string, there is a 4 in position P, then the most recent 1 must be in position >= P-2.

Time: O(N)

Space: O(N) if one stores the string, but can be done in O(1) if one computes the answer while reading the string.


## Wilbur and array
The problem can be found [here](http://codeforces.com/problemset/problem/596/B?locale=en)
and [this](code/wilbur.cpp) is my code.

If A[0...n-1] is the array, consider the quantity

W = |A[0]| + |A[1] - A[0]| + |A[2] - A[1]| + ... + |A[n-1] - A[n-2]|.

At the beginning, when the elements are all 0, W is equal to 0. When Wilbur makes a move, this number W increases or decreases exactly by 1.
Thus a lower bound on the number of moves that Wilbur has to make is given by the quantity W computed on the final array.

On the other hand, it is easy to see that this number of moves suffices. One way to realize this number of moves is to adjust A[0] first, then A[1], then A[2] and so on.

In conclusion, the answer is simply given by W, which is easily computed in linear time.
The space complexity is linear if one stores the array.


## Alternative thinking
The problem can be found [here](http://codeforces.com/problemset/problem/603/A?locale=en)
and [this](code/thinking.cpp) is my code.

The score of a binary array is given by the number of blocks of equal consecutive digits.
If the initial score is N, where N is the length of the array, the best thing to do is to flip the entire sequence to keep the same score.
If the initial score is N-1, then one can flip the prefix ending where there is a pair of consecutive 0 or 1, in order to get N as final score.
In the other cases, the best one can do in order to increase the score is choose the substring to flip in such a way as to break two of the blocks (or break one block twice).

Thus the answer is

S = initial score plus 2

or N if S > N.

Complexity: linear time, linear space (if one counts the memory needed to store the array).
