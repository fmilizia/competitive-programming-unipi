# Lectures 3 and 4 (23 and 24/09/2019)

## Inversion count
The problem can be found [here](http://www.spoj.com/problems/INVCNT/)
and [this](code/inversion-count.cpp) is my code.

I used a divide and conquer approach, which computes the answer while sorting the array at the same time.
 - Divide: just split the array in two halves;
 - Conquer: recursively sort and compute the number of inversions in each piece;
 - Merge: count, for each element x in the right hand side half, how many elements on the left hand side are greater than x.
   To obtain the answer sum these numbers and the number of inversions of each half (from the "Conquer" part).
   This can be done in linear time in total, using two pointers, one in each half (here it is crucial that each half is sorted).
   Finally merge the two arrays, as in the merge sort algorithm.

As for the merge sort algorithm, the running time is O(n log n), with the same analysis.

## Largest even number
The problem can be found [here](http://practice.geeksforgeeks.org/problems/largest-even-number/0)
and [this](code/largest-even-number.cpp) is my code.

As a first step, find the smallest even digit in the number (or the smallest odd, if all digits are odd).
This will be the last digit of the answer.
As for the rest of the digits, one simply has to sort them in descending order.

In this case a counting sort is better than a comparison based sorting algorithm, since it runs in linear time.
