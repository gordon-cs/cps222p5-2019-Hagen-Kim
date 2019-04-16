#include <iostream>
#include <list>
#include "graph.h"
#include <cstdlib>

using namespace std;


Graph::Graph(int V)
{
  numV = V;
  adj = new list[V];
}

void Graph::addEdge(int x, int y)
{
  adj.push_back(x);
  adj.push_back(y);
}

void Graph::bfs(int n)
{
  // Mark all the vertices as unvisited
  bool *visited = new bool[V];
  for (int i = 0; i < V; i++)
      visited[i] = false;

  // Create a queue
  list<int> queue;

  // Mark the current node as visited and put it into the queue
  visited[n] = true;
  queue.push_back(n);

  // Go through all adjacent vertices of the vertex
  list<int>::iterator i;

  while (!queue.empty())
  {
    // Take out the vertex from the queue
    n = queue.front();
    cout << n << " ";
    queue.pop_front();

    for (i = adj[n].begin(); i != adj[n].end(); i++)
    {
      if (!visited[*i])
      {
        visited[*i] = true;
        queue.push_back(*i);
      }
    }
  }
}

int main()
{
  int numT;
  int numR;
  string towns;
  char bflag;

  cin >> numT, numR;
  cout << "There are " << numT << " number of towns in the province, and " <<
      numR << " number of road(s)." << endl;

}
