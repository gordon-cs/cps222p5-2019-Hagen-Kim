#include <list>
#include <iostream>
using namespace std;


class Graph
{
  //RT data should be private, and indented like rest
  private:
    int numV;  // Number of vertices
    //RT Where are town names stored?
    //RT how is are adjacencies stored in this list?
    list<int> *adj;  // List of adjacency
    bool *visited;  // Boolean to check if a vertex is visited or not

  public:

    Graph(int V);  // Constructor

    void addEdge(int x, int y);  // Function to add an edge
    //RT: This declaration must match the implementation in graph.cc
    //    Currently, it causes a compile error.
    //void bfs(int n);  // Function to sort/print BFS traversal
    //    Also, need a comment here explaining each parameter clearly.
    void bfs(int **matrix, int start, int numT, string list, ostream & output);
    //RT But a better class design would have most of this as object data,
    //   so bfs() wouldn't need as many arguments.
};
