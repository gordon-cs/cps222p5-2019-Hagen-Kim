#include <iostream>
#include <list>
#include "graph.h"

using namespace std;


Graph::Graph(int V)
{
  numV = V;
  adj = new list[V];
}

void Graph::addEdge(int x, int y)
{
  adj[x].push_back(y);
  adj[y].push_back(x);
}

void Graph::bfs(int n)
{

}

int main()
{

}
