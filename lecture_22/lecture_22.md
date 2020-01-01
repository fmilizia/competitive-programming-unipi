# Lecture 22 (09/12/2019)

## Learning languages
The problem can be found [here](http://codeforces.com/problemset/problem/277/A?locale=en)
and [this](code/languages.cpp) is my code.

Build a graph with **N** + **M** nodes, one for each person and one for each language.
An edge is added between a person and a language if that person knows that language.

The answer to the problem is the number of connected components containing at least a person.

There is a special case: if everyone speak no language, then the answer in **N**.

Complexity: O(N + M) space and time.

## Checkposts
The problem can be found [here](http://codeforces.com/problemset/problem/427/C?locale=en)
and [this](code/checkposts.cpp) is my code.

The main part of the solution is finding the strongly connected components of the graph, which is done using two DFSs.

Then one must find the minimum cost of a station in each scc, and sum this value over all sccs.
Additionally, one must count how many stations in a given scc have the minimum cost, and multiply this values over all sccs.

Complexity: O(N + M) space and time.
