# Graph-Algorithms #
A project that implements different graph algorithms using C.

## Overview ##
This is a project from Rutgers Computer Science 01:198:211:05-08 COMPUTER ARCHITECTURE class taught by Prof. Santosh Nagarakatte. For this project, we were instructed to implement given algorithms when traversing given graphs. 

### Introduction ###
In this assignment, you will improve your C programming skills by implementing graph algorithms.
First, you represent a graph data structure in C by representing undirected and weighted directed
graphs. Second, you implement two simple graph traversal algorithms – breadth-first search (BFS)
and depth-first search (DFS). Third, you will use the DFS traversal to single-source shortest path
computation in directed acyclic graphs (DAGs). Lastly, you will implement Dijkstra’s shortest
path algorithm that is not limited to DAGs and can be used to find single-source shortest paths
in all directed graphs that have no edges with negative weights. Your program must follow the
input-output guidelines listed in each section exactly, with no additional or missing output.
No cheating or copying will be tolerated in this class. Your assignments will be automatically
checked with plagiarism detection tools that are powerful. Hence, you should not look at your
friend’s code or use any code from the Internet or other sources such as Chegg/Freelancer. All
violations will be reported to office of student conduct. See Rutgers academic integrity policy at:
http://academicintegrity.rutgers.edu/

### First: Undirected Graph Representation (20 Points) ###

Graphs are a widely used data structure in CS with applications in computer networks, circuits,
and neural networks. A graph consists of vertices that are connected by edges. If edges have a
direction associated with them, such graphs are called directed graphs. If the edges do not have
any direction associated with them, such graphs are called undirected graphs.

Consider the undirected graph in Figure 1(a) used to model roads between different intersections
in a city. In this example, a vertex represents an intersection. An edge models a road between a
pair of intersections. A pair of vertices are adjacent if an edge connects them. For example, in
Figure 1(a) the vertex pair (A,B) is adjacent. Further, the degree of a vertex V is defined as the
number of vertices adjacent to it. For example, in Figure 1(a), vertex E has a degree of 2 since it
is adjacent to vertex C and D.

There exist several standard ways to represent a graph on a computer. In this programming assignment, we are going to use the adjacency list representation. In the adjacency list representation,

each vertex stores a linked list of its adjacent vertices. Figure 1(b) illustrates the adjacency list
representation of the undirected graph from Figure 1(a).

In this part, you write a program that will read an undirected graph from a file. Store it in an
adjacency list representation and then answer simple graph queries.

Input-Output format: Your program will take two file names as its command-line input. The
first file includes the undirected graph. Your program reads the contents of this file and constructs
the graph data structure. The first line in this file provides the number of vertices in the graph.
Next, each line contains the name of each vertex in the graph. Afterwards, each following line
includes information about an edge in the graph. Each edge is described by the name of its pair of
vertices, separated by a space.

The second file includes queries on the constructed graph. Each line contains a separate query that
starts with the query type and a vertex, separated by a space. There are two query types. Degree
queries start with the letter ’d’, followed by a space and the vertex’s name, which is a string. Upon
processing a degree query, your program must print out the queried vertex’s degree, followed by a
newline character. Adjacency queries start with the letter ’a’, followed by a space and the vertex’s
name. Upon processing an adjacency query, your program must print out the vertices adjacent to
the queried vertex, each vertex separated by a space and finally, a newline character. When you
print the results of the adjacency query, the results have to be sorted lexicographically.

Example Execution:

Let’s assume we have the following graph and query file:

graph.txt<br />
5 <br />
A <br />
B <br />
C <br />
D <br />
E <br />
A B <br />
A C <br />
A D <br />
B D <br />
C D <br />
C E <br />
D E <br />

query.txt:

d E <br />
a C <br />
d A <br />
a A <br />
Then the result will be:

$./first graph.txt query.txt <br />
2 <br />
A D E <br />
3 <br />
B C D <br />

### Second: Weighted Directed Graph Representation (10 Points) ###

Consider the example graph in Figure 1(a). While this graph models the existence of a road
between a pair of intersections, it doesn’t capture the distance between them. Further, some roads
may not be bidirectional, which cannot be modeled using an undirected graph. In this part, we
write a program to store and query a weighted directed graph. In a weighted graph, we attribute a
numeric value to each edge. Figure 2(a) shows a weighted directed graph. As shown in Figure 2(a),
note that in a a directed graph, the inclusion of edge (A,C) does not imply the existence of edge
(C,A). Figure 2(b) visualizes the adjacency list representation of the weighted directed graph in
Figure 2(a).

In this part, you write a program that will read a weighted directed graph from a file. Store it in
an adjacency list representation and then answer simple graph queries.

Input-Output format: Your program will take two file names as its command-line input. The
first file includes the weighted directed graph. Your program reads the contents of this file and
constructs the graph data structure. The first line in this file provides the number of vertices
in the graph. Next, each line contains the name of each vertex in the graph. Afterwards, each
following line includes information about a weighted directed edge in the graph. Each weighted
edge is described by the name of its pair of vertices, followed by the edge weight, separated by a
space. For example, B A 10 defines a directed edge from vertex B to vertex A with an edge weight
of 10.

The second file includes queries on the constructed graph. Each line contains a separate query that
starts with the query type and a vertex, separated by a space. There are three query types. Outdegree queries start with the letter ’o’, followed by a space and the vertex’s name. Upon processing an out-degree query, your program must print out the queried vertex’s out-degree1, followed by a
newline character. In degree queries start with the letter ’i’, followed by a space and the vertex’s
name. Upon processing an in degree query, your program must print out the queried vertex’s in
degree2, followed by a newline character. Adjacency queries start with the letter ’a’, followed by
a space and the vertex’s name. Upon processing an adjacency query, your program must print
out the vertices adjacent to the queried vertex, each vertex separated by a space and finally, a
newline character. When you print the results of the adjacency query, the results have to be sorted
lexicographically.

Example Execution:

Let’s assume we have the following graph and query file:

graph.txt <br />
5 <br />
A <br />
B <br />
C <br />
D <br />
E <br />
B A 10 <br />
A C 8 <br />
A D 12 <br />
B D 5 <br />
C E 5 <br />
D C 9 <br />
E C 7 <br />
E D 3 <br />

query.txt: <br />
o E <br />
a C <br />
i E <br />
a A <br />
a E <br />

Then the result will be: <br />
$./second graph.txt query.txt <br />
2 <br />
E <br />
1 <br />
C D <br />
C D <br />

### Third: Breadth-first Search (BFS) (20 points) ###
In this part, you will implement the bread-first search (BFS) graph traversal algorithm. For a given
input graph G=(V,E) and a source vertex s, BFS starts exploring the edges of G until it discovers all
vertices reachable from the source vertex. During a BFS search, we start by visiting the adjacent
vertices to the source vertex, processing them, and subsequently exploring vertices in order of edge
distance (i.e., the smallest number of edges) from it. Figure 3 shows an example graph and its
BFS traversal starting from source vertex B. Note that the vertices are processed in order of their
distance from the source3.

You will write a program that will read an undirected graph from a file using your implementation
from part 1 and perform BFS starting from different source vertices.

Input-Output format: Your program will take two file names as its command-line input. The
first file includes the undirected graph. This file is similar to the graph file from part 1. Your
program reads the contents of this file and constructs the graph data structure. The first line in
this file provides the number of vertices in the graph. Next, each line contains the name of each
vertex in the graph. Afterwards, each following line includes information about an edge in the
graph. Each edge is described by the name of its pair of vertices, separated by a space.
The second file includes BFS queries on the constructed graph. Each line contains a different BFS
query specifying a source vertex for the BFS. Your program must read the source vertex, perform
a BFS traversal on the constructed graph using the chosen source vertex, and print out the graph
vertices in order of BFS processing. Each vertex is separated by a space and finally, a newline
character.

Example Execution:

Let’s assume we have the following graph and query file:

graph.txt <br />
6 <br />
A <br />
B <br />
C <br />
D <br />
E <br />
F <br />
A B <br />
A C <br />
A D <br />
B D <br />
C D <br />
C E <br />
D E <br />
E F <br />

query.txt: <br />
B <br />
E <br />

Then the result will be:

$./third graph.txt query.txt <br />
B A D C E F <br />
E C D F A B <br />

### Fifth: Single-source Shortest Path in a Directed Acyclic Graph (DAG) (40 points) ###

Given a weighted directed graph G=(V,E) and the source vertex s, the single-source shortest path
problem’s goal is to identify the shortest path from the source vertex to all vertices in the graph.
For example, finding the shortest path from our home to different adjacent cities can be modeled
as a single-source shortest path problem with our home being the source vertex.

Depending on the input graphs type, a single-source shortest path problem can be solved using
different algorithms that vary in asymptotic running time and complexity. For example, the BFS
algorithm from part 3 is sufficient to solve the single-source shortest path problem for unweighted
Figure 5: This figure illustrates a directed graph and the steps involved in identifying its topological
sort
graphs. However, we need other algorithms to solve the single-source shortest path problem in
weighted graphs.

In this part, your task is to write a program to solve the single-source shortest path problem for a
type of directed called directed acyclic graphs (DAG). A DAG is a directed graph with no cycles.

The single-source shortest problem in DAGs can be solved by visiting the DAG’s vertices in a
topologically sorted order and updating the shortest path of the visited vertex’s adjacent vertices.
You must use the DFS traversal from part 4 to topologically sort the DAG.

Algorithm 1 shows the steps to compute the single source path for the graph G and source vertex
src. The algorithm maintains a distance array that is initially set to infinity for all vertices except
the source vertex. distance[u] contains the shortest path from the source vertex to vertexu at
the end of the algorithm or infinity if no path between src and u exists.

A topological sorting of the a DAG G(V,E) is an ordering of its vertices, T such that for every directed (u,v), vertex u appears before vertex v in its topological ordering. For example, Figure 5(a) shows an example DAG and its topological sort. Figure 5(b-f) illustrates the steps taken by the
DFS inspired algorithm to compute the topological ordering of the DAG by using a stack. Lastly
Figure 5(g) shows updates to the distance array by using algorithm Algorithm 1 on the DAG from
Figure 5(a).

Input-Output format: Your program will take two file names as its command-line input. This
first file includes a DAG, and it follows the same format from parts 2 and 4. Your program reads the
contents of this file and constructs the graph data structure. The first line in this file provides the
number of vertices in the DAG. Each following line includes information about a weighted directed
edge in the DAG. Each weighted edge is described by the name of its pair of vertices, followed by
the edge weight, separated by a space. Your program must read and construct this DAG.

The second file includes single source shortest path queries on the constructed DAG. Each line
contains a different single-source shortest path query by specifying a source vertex. Your program
must read the source vertex, perform the single source shortest path algorithm using the provided
source vertex, and print out each of vertex in the DAG in lexicographic ordering, followed by the
length of the shortest path to that vertex, and a newline character. Note that an additional newline
character follows the last vertex in DAG. Further, your program must detect if the input graph is
not a DAG. In such cases, your program simply prints out CYCLE, followed by a newline character.

Example Execution:

Let’s assume we have the following graph input file:

graph.txt <br />
7 <br />
A <br />
B <br />
C <br />
D <br />
E <br />
F <br />
G <br />
A D 10 <br />
A C 5 <br />
B D 7 <br />
C D 3 <br />
D E 5 <br />
E F 1 <br />
C F 10 <br />
E G 10 <br />
F G 5 <br />

query.txt <br />
A <br />
G <br />

Then the result will be: <br /> 
$./fifth graph.txt query.txt <br />
A 0 <br />
B INF <br />
C 5 <br />
D 8 <br />
E 13 <br />
F 14 <br />
G 19 <br />
A INF <br />
B INF <br />
C INF <br />
D INF <br />
E INF <br />
F INF <br />
G 0 <br />

For the scenario when the input graph is not a DAG: <br />
not_dag.txt <br />
2 <br />
CA <br />
NJ <br />
NJ CA 3000 <br />
CA NJ 3100 <br />

query.txt <br />
CA <br />

Then the result will be: <br />
$./fifth not_dag.txt query.txt <br />
CYCLE <br />

### Sixth: Dijkstra’s Shortest Path Algorithm (40 points) ###

In this part, we implement Dijkstra’s Algorithm. This algorithm solves the single-source shortest
path problem for graphs with nonnegative edge weights. The key idea behind Dijkstra’s algorithm
is to maintain a set of vertices whose final shortest path from the source vertex has been determined.
This set starts empty, and at each iteration of the algorithm, we add the next vertex by extracting it
from a min-priority queue of vertices. For more information on Dijkstra’s shortest path algorithm,
see https://bit.ly/3hToIy5.

Input-Output format: Your program will take two file names as its command-line input. This
first file includes a weighted directed graph, and it follows the same format from parts 2 and 4.
Your program reads the contents of this file and constructs the graph data structure. The first line
in this file provides the number of vertices in the graph. Each following line includes information
about a weighted directed edge in the graph. Each weighted edge is described by the name of its
pair of vertices, followed by the edge weight, separated by a space. Your program must read and
construct this graph.

The second file includes single source shortest path queries on the constructed each. Each line
contains a different single-source shortest path query by specifying a source vertex. Your program
must read the source vertex, perform Dijkstra’s single-source shortest path algorithm using the
provided source vertex, and print out each of vertex in the graph in lexicographical ordering,
followed by the length of the shortest path to that vertex, and a newline character. Note that an
additional newline character follows the last vertex in DAG.

Example Execution:

Let’s assume we have the following graph input file:

graph.txt <br />
5 <br />
A <br />
B <br />
C <br />
D <br />
E <br />
B A 10 <br />
A C 8 <br />
A D 12 <br />
B D 5 <br />
C E 5 <br />
D C 9 <br />
E C 7 <br />
E D 3 <br />

query.txt: <br />
A <br />
E <br />

Then the result will be:<br />
$./sixth graph.txt query.txt <br />
A 0 <br />
B INF <br />
C 8 <br />
D 12 <br />
E 13 <br />
A INF <br />
B INF <br />
C 7 <br />
D 3 <br />
E 0 <br />

