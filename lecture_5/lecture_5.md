# Lecture 5 (30/09/2019)

## Firing employees
The problem can be found [here](http://practice.geeksforgeeks.org/problems/firing-employees/0)
and [this](code/firing-employees.cpp) is my code.

The sieve of Eratosthenes is used (even before reading the testcases) to 
determine a vector of booleans telling if each number up to 200000 is prime or not.
To solve a tescase the tree is traversed level by level, with the help of a queue (it is a BFS).
It is easy to compute the depth of each node, and thus the answer.

Complexity: that of the sieve, plus linear time for each testcase.

## Check for BST
The problem can be found [here](http://practice.geeksforgeeks.org/problems/check-for-bst/1)
and [this](code/check-for-bst.cpp) is my code.

I use an auxilary function which takes as arguments a node and two numbers, which are the
lower and upper bound on the possible values of the descendants of the node, and outputs wheter
the subtree is a BST or not. It is a simple recursive function.

Complexity: linear in the size of the tree.

## Preorder traversal and BST
The problem can be found [here](http://practice.geeksforgeeks.org/problems/preorder-traversal-and-bst/0)
and [this](code/preorder-traversal-and-bst.cpp) is my code.

An array arr represents a BST if and only if, every time there are two indices i<j such that
arr[i] < arr[j], then arr[i] < arr[k] for every k greater than j.

One can show the preceding assertion by induction on the number of nodes (= elements of the array).

Now that we have this description of the arrays that represent a BST, we can solve the 
problem reading the array and using a queue.
This queue keeps track of the indices i for which we have not found the respective j yet.
When the index i exits the queue, a lower bound for the following values is updated.

Complexity: linear in time and space.

## Maximum path sum
The problem can be found [here](http://practice.geeksforgeeks.org/problems/maximum-path-sum/1)
and [this](code/maximum-path-sum.cpp) is my code.

I use an auxilary function which computes the maximum sum from a node down to a leaf.
It is recursive and very simple. It also updates the answer to the problem on the fly,
considering the maximum result going down to the right and that obtained going down to the left.

Complexity: linear.
