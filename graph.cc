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
#include <fstream>
#include <stack>


// Define constructor of class Graph
Graph::Graph(std::string fileName)
{
  file = fileName;
}

// Destructor of class Graph
Graph::~Graph()
{ }

// Return vertices
std::deque<Vertex *> Graph::getVertexList()
{
  return vertices;
}

// Add a vertex to the deque of vertices
void Graph::addVertex(Vertex *v)
{
  vertices.push_back(v);
}

// Operate BFS traversal
/*
 * Jahnuel helped me by explaining more of what needed to be done for the BFS traversal function
 */
std::deque<std::string> Graph::BFS()
{
  // Mark all vertices as unvisited
  std::deque<std::string> toVisit, traversal;
  std::string cityName;

  Vertex *current = vertices.at(0);
  toVisit.push_back(current -> getName());
  traversal.push_back(current -> getName());

  while(!toVisit.empty())
  {
    current = getVertex(toVisit.front());
    toVisit.pop_front();

    for (int j = 0; j < current -> getEdgeList().size(); j++)
    {
      Edge *e = current -> getEdgeList().at(j);

      if (e -> getCityOneName() == current -> getName())
      { 
          cityName = e->getCityOneName();
      }
      else 
      {
          cityName = e->getCityTwoName();
      }

      if (find(traversal.begin(), traversal.end(), cityName) == traversal.end()
        && find(toVisit.begin(), toVisit.end(), cityName) == toVisit.end())
        {
          toVisit.push_back(cityName);
          traversal.push_back(cityName);
        }
    }
  }
  return traversal;
}

// Get vertex of a city
Vertex* Graph::getVertex(std::string citiesName)
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

  bool isBridge = false;

  if (!isBridge)
  std::vector<Edge *> getEdgeList();

  for (std::deque<Vertex *>::iterator i = vertices.begin(); (i == vertices.end()); ++i)
  {
    std::cout << "The input data is: " << std::endl;

    Edge *curr = 
    std::cout << cityNames.getWeight() << " mi " <<std::endl;

    if (isBridge)
      std::cout << "via bridge " << std::endl;


  }




}

// Read files
void Graph::readFile()
{

  std::ifstream inFile;

}

std::stack<std::string> DFS(int s)
{
  // Mark all vertices as unvisited
  std::stack<std::string> toVisit;
  std::string cityName;

  std::cout<< "If all bridges fail, the following towns would form an isolated group: " <<std::endl;

}

// Define constructor of class Vertex
Vertex::Vertex(std::string name, bool capital)
{
  cityName = name;
  isCapital = capital;
}

// Destructor of a class Vertex
Vertex::~Vertex()
{ }

// Get name of a vertex
std::string Vertex::getName()
{
  return cityName;
}

// Add an edge to the list of edges
void Vertex::addEdge(Edge *e)
{
  edges.push_back(e);
}

// Get edge list
std::vector<Edge *> Vertex::getEdgeList()
{
  return edges;
}

// Check if a vertex is capital or not
bool Vertex::isVertexCapital()
{
  return isCapital;
}

// Define constructor of class Edge
Edge::Edge(std::string city1, std::string city2, bool bridge, int weight)
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
std::string Edge::getCityOneName()
{
  return cityOne;
}

// Return name of city2
std::string Edge::getCityTwoName()
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
