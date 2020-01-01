# Lecture 21 (03/12/2019)

## X total shapes
The problem can be found [here](http://practice.geeksforgeeks.org/problems/x-total-shapes/0)
and [this](code/shapes.cpp) is my code.

The solution is a DFS that visits the X cells.
Every time a new visit is started, the answer increases by 1.

Time: O(NM). Space: O(NM)

## Is bipartite
The problem can be found [here](http://practice.geeksforgeeks.org/problems/bipartite-graph/1)
and [this](code/bipartite.cpp) is my code.

The nodes are colored with two colors (**1** and **2**) during a DFS.
If a node is already colored with the wrong color, the graph is not bipartite.

Time: O(V^2). Space: O(V^2)

## Fox and names
The problem can be found [here](http://codeforces.com/problemset/problem/510/C?locale=en)
and [this](code/fox.cpp) is my code.

The first step is building a graph with letters of the alphabet as nodes.
A directed edge between two letters means that the first one must preceed the other in the ordering we have to determine.
The number of edges is equal to the number of strings minus 1 (an edge is added for every pair of consecutive strings).

Then a topological sort of the graph determines a possible ordering.

Time and space: O(sum of lenght of the strings + A), where A is the number of letters in the alphabet.
