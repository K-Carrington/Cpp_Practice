/*
WeightedGraphDijkstra_test.cpp     Ken Carrington
May 2015

The input file contains an adjacency list representation of an undirected weighted
graph with 200 vertices labeled 1 to 200. Each row consists of the node tuples
that are adjacent to that particular vertex along with the length of that edge.

For example, the 6th row has 6 as the first entry indicating that this row
is the vertex labeled 6. The next entry of this row "141,8200"
indicates that there is an edge between vertex 6 and vertex 141 that has
length 8200. The rest of the pairs of this row indicate the other vertices
adjacent to vertex 6 and the lengths of the corresponding edges.

*/

#include "WeightedGraphDijkstra.hpp"
#include <fstream>

int read_graph(Weighted_Graph &g)
  {
    string big_fn = "C:\\Software_Engineering\\Stanford_Algorithms_Class\\ProgQ5\\dijkstraData.txt";
    string m_fn = "C:\\Software_Engineering\\Stanford_Algorithms_Class\\ProgQ5\\dijkstra_m.txt";
    string s_fn = "C:\\Software_Engineering\\Stanford_Algorithms_Class\\ProgQ5\\dijkstra_sm.txt";
    string vs_fn = "C:\\Software_Engineering\\Stanford_Algorithms_Class\\ProgQ5\\dijkstra_vsm.txt";

    string filename;
    cout << "Enter IN CAPS: B, M, S or V) (for big, medium, small or very small test file)\n";
    cin >> filename;

    if (filename == "V")      filename = vs_fn;
    else if (filename == "S") filename = s_fn;
    else if (filename == "M") filename = m_fn;
    else                      filename = big_fn;

    //Read array and get length
    ifstream graph_file (filename.c_str());
    string line;
    if (graph_file.is_open())
    {
      while ( getline (graph_file,line) )
      {
        //  cout << "line read in: " << line << endl;
          g.add_vertex(line); // TBD put in if need to error check
      }
      graph_file.close();
    }
    else { cout << "Unable to open file " << filename << endl; return -1; }

    cout << "num verticies = " << g.num_verticies() << endl;

    if (g.num_verticies() == 1) return 0;
    return g.num_verticies();
}

int main()
{
    Weighted_Graph g;
    read_graph(g);
    //g.print_graph();

    g.shortest_paths_from_1_to_all();

    cout << "Fin!" << endl;
    return 0;
}
