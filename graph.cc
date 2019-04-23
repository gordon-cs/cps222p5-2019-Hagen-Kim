/*
 * Project 5
 * Jenny and FeiFei
 * Got help from Jahnuel
 *
 */

#include "graph.h"
#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <map>
#include <vector>

using namespace std;

// Define constructor of class Graph
Graph::Graph(string fileName)
{
  file = fileName;
}

// Destructor of class Graph
Graph::~Graph()
{ }

// Return vertices
deque<Vertex *> Graph::getVertexList()
{
  return vertices;
}

// Add a vertex to the deque of vertices
void Graph::addVertex(Vertex *v)
{
  vertices.push_back(v);
}

// Operate BFS traversal
deque<string> Graph::BFS()
{
  // Mark all vertices as unvisited
  bool visited = new bool [vertices];
  for (int i = 0; i < vertices; i++)
    visited[i] = false;

  // Create a deque
  deque<Vertex *> toVisit;
  start = vertices.front();
  toVisit.push_back(start);
  visited[start] = true;

  while (!toVisit.empty())
  {
    curr = toVisit.front();
    toVisit.pop();

    for (int j = 0; j < vertices; j++)
    {
      if (toVisit[curr] != 0 && (!visited[j]))
      {
        toVisit.push_back(j);
        visited[j] = true;
      }
    }

  }
}

// Get vertex of a city
Vertex* Graph::getVertex(string citiesName)
{
  // Go through all vertices/cities
  for (int x = 0; x < vertices.size(); x++)
  {
    // Return the name of city if found
    if (vertices.at(x)->getName() == citiesName)
    {
      return vertices.at(x);
    }
  }
  // If city is not found, that means it doesn't exist -- so return NULL
  return NULL;
}

// Print
void Graph::print()
{

}

// Read files
void Graph::readFile()
{

}

// Define constructor of class Vertex
Vertex::Vertex(string name, bool capital)
{
  cityName = name;
  isCapital = capital;
}

// Destructor of a class Vertex
Vertex::~Vertex()
{ }

// Get name of a vertex
string Vertex::getName()
{
  return cityName;
}

// Add an edge to the list of edges
void Vertex::addEdge(Edge *e)
{
  edges.push_back(e);
}

// Get edge list
vector<Edge *> Vertex::getEdgeList()
{
  return edges;
}

// Check if a vertex is capital or not
bool Vertex::isVertexCapital()
{
  return isCapital;
}

// Define constructor of class Edge
Edge::Edge(string city1, string city2, bool bridge, int weight)
{
  cityOne = city1;
  cityTwo = city2;
  isBridge = bridge;
  weightOfEdges = weight;
}

// Destructor of a class Edge
Edge::~Edge()
{ }

// Return name of city1
string Edge::getCityOneName()
{
  return cityOne;
}

// Return name of city2
string Edge::getCityTwoName()
{
  return cityTwo;
}

// Return boolean checking edges as bridge
bool Edge::isEdgeBridge()
{
  return isBridge;
}

// Return weight of edges
int Edge::getWeight()
{
  return weightOfEdges;
}

// Main function
int main()
{

}
