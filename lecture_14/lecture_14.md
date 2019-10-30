# Lecture 14 (29/10/2019)

All the problems in this lecture are solved using a heavy-light decomposition, 
reducing the original problem (which is on a tree) to the same problem on an array.

## QTREE
The problem can be found [here](https://www.spoj.com/problems/QTREE/)
and [this](code/qtree.cpp) is my code.


## QTREE2
The problem can be found [here](https://www.spoj.com/problems/QTREE2/)
and [this](code/qtree2.cpp) is my code.


## QTREE3
The problem can be found [here](https://www.spoj.com/problems/QTREE3/)
and [this](code/qtree3.cpp) is my code.


## GOT
The problem can be found [here](https://www.spoj.com/problems/GOT/)
and [this](code/got.cpp) is my code.

The above problems were discussed in class; I implemented the solutions suggested by the professor.


## Chef and the tree
The problem can be found [here](https://www.codechef.com/problems/CHEFTREE)
and [this](code/cheftree.cpp) is my code.

The problem on an array V[0,n-1] is the following.

A constant C is given (actually, the original problem gives two constants A and B, but the conditions can be simplified).
We have to support the following operations:
 - increase every value in the range V[l,r] by a positive amount w;
 - count how many values in the range V[l,r] are greater than or equal to C.

I implemented a solution using a segment tree and a Fenwick tree.
The segment tree supports the following operations:
 - increase every value in the range V[l,r] by an amount w (positive or negative);
 - find the position in the range [l,r] with maximum value.
The Fenwick tree supports the following operations on an array H[0,n-1]:
 - increase the value H[i] by 1
 - compute the sum of the elements in a range (it actually computes the sums of prefixes. With a subtraction one gets the sum of a range).

Then, here is how I implemented the operations that are needed:
 - increase: just do the operation on the segment tree.
 - count: find the maximum value in the range (asking the segment tree). Suppose it is in position p, and the value is val.
   If val >= C, tell the Fenwick tree to increase the value in position p, and tell the segment tree to decrement the value in position p making it very very small.
   Now the answer to the query can be found with a query to the Fenwick tree, asking the sum in the given range.
