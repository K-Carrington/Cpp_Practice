/*
Ken Carrington, Coursera Stanford Algorithms Programming Assignment 5
May 2015

Dijkstra's shortest-path algorithm.

Dijkstra's shortest-path algorithm on a graph, using 1 (the first vertex) as the source,
computes the shortest-path distances between 1 and every other vertex of the graph.
If there is no path between a vertex v and vertex 1, defines the shortest-path distance
between 1 and v to be 1000000.
*/

#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <stack>
#include <iterator>
#include <cstdlib>

using namespace std;

class Weighted_Graph
{
private:
    //a hash table (from_node, (to_node, length))
    unordered_map<int, const unordered_map<int, int>> vertices;

public:
    // Put information into an object of this class:
    int add_vertex(string v);

    // Get information from an object of this class:
    //after reading the graph, this verifies the number of vertices
    int num_verticies();

    //for debug purposes to thoroughly verify the input file
    void print_graph();

    //computes shortest path from nodes numbered by start to node finish
    unordered_map<int, int> shortest_path(int start, int finish);

    //computes shortest paths from 1 to 2, 1 to 3, ... 1 to n
    void shortest_paths_from_1_to_all();
};


