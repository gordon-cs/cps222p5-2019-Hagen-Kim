#include <list>
#include <iostream>


class Graph
{
  int numV;  // Number of vertices
  list *adj;  // List of adjacency
  bool *visited;  // Boolean to check if a vertex is visited or not

  public:

    Graph(int V);  // Constructor

    void addEdge(int x, int y);  // Function to add an edge
    void bfs(int n);  // Function to sort/print BFS traversal
}
