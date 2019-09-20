# Lecture 1 (16/09/2019)

## Leaders in array
The problem can be found [here](http://practice.geeksforgeeks.org/problems/leaders-in-an-array/0)
and [this](code/leaders-in-array.cpp) is my code.

Scan the array from right to left,
updating at every step the maximum between the numbers seen so far.

The current number is a leader if it is greater than (or equal to) the current maximum. 
I use a vector of booleans to remember, for each position, if the corresponding number is a leader or not.

The algorithm is linear in both time and space.

## Kadane's algorithm
The problem can be found [here](http://practice.geeksforgeeks.org/problems/kadanes-algorithm/0)
and [this](code/kadanes-algorithm.cpp) is my code.

This is a classical algorithm; the solution requires linear time and constant space (apart from the space used to store the array).

Scan the array from left to right; at every step the candidate subarray is either
enlarged, adding an element to the right, or completely discarded, leaving in it only the new element
(this is done when its sum is less than zero).

The solution is correct because one can easily show by induction that at every step, if you are at position i,
you are considering the maximum sum of a subarray ending at position i.

## Missing number in array
The problem can be found [here](http://practice.geeksforgeeks.org/problems/missing-number-in-array/0)
and [this](code/missing-number-in-array.cpp) is my code.

The missing number can be determined by computing the xor of all the elements of the array and of the numbers from 1 to n.
Alternatively one could compute the sum of the elements and subtract it from the sum of the numbers from 1 to n (but this could be large, not fitting in an int. 
One should use 64-bit integers or overcome the problem in other ways, like doing the computation modulo n, or modulo a big enough power of 2. Actually 
one could even compute normal sums and use 32-bit integers and still get the correct solution, since this morally means working modulo a power of 2).

## Trapping rain water
The problem can be found [here](http://practice.geeksforgeeks.org/problems/trapping-rain-water/0)
and [this](code/trapping-rain-water.cpp) is my code.

I have found a solution which runs in O(N) time and takes O(1) space (apart from the space used to store the array).

As we said during the lesson, the amount of water at position i is equal to
min(max_left(i), max_right(i)) - A(i),
where max_left(i) is the maximum A(j) for j <= i, and max_right(j) is the maximum for j >= i. 

If we denote by M the maximum value in the array one can easily see that max(max_left(i), max_right(i)) = M for every i.
Now we can write min(max_left(i), max_right(i)) = max_left(i) + max_right(i) - M.

Now that we have got rid of that min, it is easy to compute the answer scanning the array twice, without the need to store O(N) additional integers.


## Sliding window maximum
The problem can be found [here](http://practice.geeksforgeeks.org/problems/maximum-of-all-subarrays-of-size-k/0)
and [this](code/maximum-of-all-subarrays-of-size-k.cpp) is my code.

This classical problem can be solved in O(N) time and O(k) additional space using a deque.

The idea is that while we read the array the deque stores a set of ''possibly useful'' previous elements, that are either big or recent.
In fact, on every step, it stores a list of *leaders* (see the first problem) of the current window. Every time the window moves one step to the right the deque is updated removing too old elements from one end
and too small elements (that is, smaller than the current element) from the other end, and adding the new element.

In my implementation the deque actually stores the positions and not the values (which can easily be read from the array once one knows the position).
