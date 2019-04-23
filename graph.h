#include <iostream>
#include <map>
#include <string>
#include <queue>

using namespace std;


class Graph
{
  int numV;  // Number of vertices
  list<int> *adj;  // List of adjacency
  bool *visited;  // Boolean to check if a vertex is visited or not

  public:

    Graph(istream & source);  // Constructor

    // Destructor
    ~Graph()
    {
      for (int i = 0; i < numT; i++)
          delete [] _roadGraph[i];
      delete [] _roadGraph;
    }

    // BFS traversal search
    void bfs();

  private:

    int numT; // Number of towns
    int numE; // Number of edges
    string * nameT; // Name of towns

    double ** _roadGraph;  // 

};
