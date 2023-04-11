## About
### Introduction
The methodology of School 21 makes sense only if peer-to-peer reviews are done seriously. Please read all guidelines carefully before starting the review.
- Please, stay courteous, polite, respectful and constructive in all communications during this review.
- Highlight possible malfunctions of the work done by the person and take the time to discuss and debate it.
- Keep in mind that sometimes there can be differences in interpretation of the tasks and the scope of features. Please, stay open-minded to the vision of the other.

### Guidelines
- Evaluate only the files that are in src folder on the GIT repository of the student or group.
- Ensure to start reviewing a group project only when the team is present in full.
- Use special flags in the checklist to report, for example, an “empty work” if repository does not contain the work of the student (or group) in the src folder of the develop branch, or “cheat” in case of cheating or if the student (or group) are unable to explain their work at any time during review as well as if one of the points below is not met. However, except for cheating cases, you are encouraged to continue reviewing the project to identify the problems that caused the situation in order to avoid them at the next review.
- Doublecheck that the GIT repository is the one corresponding to the student or the group.
- Meticulously check that nothing malicious has been used to mislead you.
- In controversial cases, remember that the checklist determines only the general order of the check. The final decision on project evaluation remains with the reviewer.
- Check whether the feedback form is filled or not (https://forms.yandex.ru/cloud/64181dc7c769f102064293e1/)

## Main part
### Depth and breadth traversal of a graph
- The libraries s21_graph and s21_graph_algorithms are developed in C++ language of C++17 standard
- The code of the libraries are in the src folder
- The program is built using Makefile with standard set of targets for GNU-programs: all, clean, test, s21_graph.a, s21_graph_algorithms.a
- Executing the "all" target leads to the correct build of the program
- Unit-tests cover all the methods
- Tests are run and work without errors
- There is no code duplication
- No goto statement is used
- LoadGraphFromFile (read graph from file), ExportGraphToDot (export graph to Dot file) methods are implemented in the Graph class
- DepthFirstSearch (depth traversal of a graph), BreadthFirstSearch (breadth traversal of a graph) methods are implemented in the GraphAlgorithms class
- Correct exception throwing is applied to the methods that simply possible errors (wrong input/output and so on)

### Finding Shortest Paths in a Graph
- GetShortestPathBetweenVertices (Dijkstra's algorithm), GetShortestPathsBetweenAllVertices (Floyd-Warshall algorithm) methods are implemented in the GraphAlgorithms class
- Methods correctly handle situations when there is no path between vertices (the first vertex is not reachable from the second one)
- The method should work correctly in cases where the graph was not preloaded
- The author of the code is able to explain the output result and the algorithm

###  Finding the minimum spanning tree
- GetLeastSpanningTree (Prim's algorithm) method is implemented in the GraphAlgorithms class
- Method correctly handle situations when there is no minimum spanning tree in the graph at all
- The method should work correctly in cases where the graph was not preloaded
- The author of the code is able to explain the output result and the algorithm

### The traveling salesman problem
- SolveTravelingSalesmanProblem (Ant colony algorithm) method is implemented in the GraphAlgorithms class
- The method should work correctly in cases where the graph was not preloaded
- The author of the code is able to explain the output result and the algorithm

### Console Interface
- The program allows you to load a graph from a file in which the graph is represented as an adjacency matrix
- The program allows you to do breadth first search in the graph and output the result into the console
- The program allows you to do depth first search in the graph and output the result into the console
- The program allows you to get the shortest path between any two vertices and output the result to the console
- The program allows you to get the shortest paths between all pairs of vertices in a graph with the output of the resulting adjacency matrix to the console
- The program allows you to get the minimum spanning tree in the graph with the output of the resulting adjacency matrix to the console
- The program allows you to get a solution to the traveling salesman problem with the output of the resulting route and its length to the console

## Bonus part
### Comparison of methods for solving traveling salesman problems
- Two more algorithms for solving the traveling salesman problem should be implemented in GraphAlgorithms class
- The console interface should provide the ability to conduct a comparative analysis of algorithms by time characteristic
- The situation in which the graph is not loaded should be handled correctly
- As a result of the analysis, the execution time for solving the traveling salesman problem using various algorithms should be shown
