/*
Ken Carrington

Weighted_Graph class implementation (including Dijkstra's shortest path algorithm)
May 2015

See WeightedGraphDijkstra.hpp file for definitions
*/

#include "WeightedGraphDijkstra.hpp"

int Weighted_Graph::add_vertex(string v)
{
    stringstream stream(v);

    int name;
    unordered_map<int, int> edges;
    string node_to;
    // read in one name and many a,b edge pairs off of the line v
    if (stream >> name)
    {
      //cout << "name: " << name << endl;
      while (stream >> node_to)
      {
        char * pch;
        pch = strtok (const_cast<char *>(node_to.c_str()),",");
        int node = atoi(pch);
        pch = strtok (NULL, ",");
        int length = atoi(pch);
        //cout << "  node: " << node << " length: " << length << endl;
        edges.insert(unordered_map<int, int>::value_type(node, length));
      }

      if (name == 0 ) //|| edges.size() == 0)
        cout << "ERROR vertex " << name << " is 0" << endl; // or adj " << " is 0" << endl;

      vertices.insert(unordered_map<int, const unordered_map<int, int>>::value_type(name, edges));
    }
    else
    {
      return 0; //error
    }
    return 1;
}

int Weighted_Graph::num_verticies()
{
    return vertices.size();
}

void Weighted_Graph::print_graph()
{
    string ans;
    int ctr = 0;
    for(unordered_map<int,const unordered_map<int, int>>::iterator ii=vertices.begin(); ii!=vertices.end(); ii++)
    {
        cout << "node_from: " << (*ii).first << endl;
        unordered_map<int, int> adjs = (*ii).second; //same as: (g[(*ii).first]);
        for(unordered_map<int, int>::iterator jj=adjs.begin(); jj!=adjs.end(); jj++)
        {
            cout << "  node_to: " << (*jj).first << ", length: " << (*jj).second << endl;
        }
        if (++ctr == 10)
        {
          ctr = 0;
          cout << "Next?\n";
          cin >> ans;
        }
    }
}

// Dijkstra's algorithm:
unordered_map<int, int> Weighted_Graph::shortest_path(int start, int finish)
{
    string ans;
    unordered_map<int, int> distances;
    unordered_map<int, int> previous;
    vector<int> nodes;
    unordered_map<int, int> path; // list of shortest path nodes and each value to return

    auto comparator = [&] (int left, int right) { return distances[left] > distances[right]; };

    //pre-processing loop
    for (auto& vertex : vertices)
    {
        if (vertex.first == start)
        {
            distances[vertex.first] = 0;
        }
        else
        {
            distances[vertex.first] = 1000000; // numeric_limits<int>::max();
        }

        nodes.push_back(vertex.first);
        push_heap(begin(nodes), end(nodes), comparator);
    }

    //Wile haven't made it to V yet
    while (!nodes.empty())
    {
        pop_heap(begin(nodes), end(nodes), comparator);
        int smallest = nodes.back();

        nodes.pop_back();

        if (smallest == finish)
        {
            while (previous.find(smallest) != end(previous))
            {
                path[smallest] = distances[smallest]; // loading path with distances
                smallest = previous[smallest];
            }
            break;
        }

        if (distances[smallest] == 1000000) // numeric_limits<int>::max())
        {
          break;
        }

        //Pick edge that minimizes the score
        for (auto& neighbor : vertices[smallest]) // go through the edges
        {
            int alt = distances[smallest] + neighbor.second;
            if (alt < distances[neighbor.first]) // if score is minimized
            {
              distances[neighbor.first] = alt;
              previous[neighbor.first] = smallest;
              make_heap(begin(nodes), end(nodes), comparator);
            }
        }
    }
    return path;
}

// Gets the shortest path and outputs the accumulating distances
void Weighted_Graph::shortest_paths_from_1_to_all()
{
    unordered_map<int, int> shortest_distances;
    string ans;

    for (auto& ii : vertices)
    {
      cout << "node_from: " << ii.first << endl;
      if (ii.first == 1) continue;

      cout << "Calling shortest_path for nodes 1 to " << ii.first << endl;
      unordered_map<int, int> path = shortest_path(1, ii.first);
      int dist;
      for (auto& node : path)
      {
        cout << "  SPoutput: node " << node.first << ", path " << node.second << endl;
        dist = node.second;
      }
      shortest_distances[ii.first] = dist;
      cout << "shortest distance to " << ii.first << " = " << dist << endl;
    }
}

