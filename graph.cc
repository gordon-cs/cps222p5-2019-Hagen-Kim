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

// Define constructor of class Graph
Graph::Graph(string fileName)
{
  file = fileName;
  // file.open(fileName);
  // readFile();
  // print();
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
/*
 * Jahnuel helped me by explaining more of what needed to be done for the BFS traversal function
 */
deque<string> Graph::BFS()
{  
  deque<string> toVisit, traversal;
  string cityName;

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

// Print graph
void Graph::print()
{
  std::deque<std::string> bfs = BFS();
  std::deque<std::string>::iterator it = bfs.begin();
  std::cout << "The input data is: " << std::endl;
  std::cout << std::endl;

  while (it != bfs.end())
  {
    Vertex *curr = getVertex(*it);
    std::cout << curr -> getName() << std::endl;
    std::vector<Edge *> edges = curr -> getEdgeList();

    for (int i = 0; i < edges.size(); i++)
    {
      std::string edgeName;
      std::string bridge = "";
      Edge *e = edges.at(i);

      if (e->getCityOneName() == curr->getName())
        edgeName = e->getCityTwoName();
      else 
        edgeName = e->getCityOneName();

      if (e->isEdgeBridge() == true)
        bridge = "via bridge";

      std::cout << "\t" << edgeName << " " << e->getWeight() << "mi " << bridge << std::endl;
    }
    it++;
  }
}

// Read files
void Graph::readFile(ifstream fileInput)
{
  // Parameters (String) -- line : to get input from the file (takes in a line at a time)
  //                 numOfCities : to have the total amount of vertices (appears on the first of first line of the input) ex. "3 2" - 3
  //                 numOfRoads : to have the total amount of edges (appears on the second of first line of the input) ex "3 2" - 2
  //                 segment : temporary string to break apart the variable "line" into different things
  // Parameter (Vector) -- list : to hold each "segment" that is created when splitting a line (will hold every word in a line)
  std::string line, numOfCities, numOfRoads, segment;
  std::vector<std::string> list;
  bool isCapital = true;

  // Read a line from a file
  while (getline(fileInput, line))
  { 
    std::stringstream ss(line);
    // Split the line by space into a list
    while (getline(ss, segment, ' '))
    {
      list.push_back(segment);
    }
    // Check if a line has two segments -- number of towns and roads
    if(list.size() == 2)
    {
      numOfCities = list.at(0);
      numOfRoads = list.at(1);
    }
    else if (list.size() == 1)
    {
      if (isCapital)
      {
        Vertex *v = new Vertex(list.at(0), true);
        isCapital = false;
        addVertex(v);
      }
      else 
      {
        Vertex *v = new Vertex(list.at(0), false);
        addVertex(v);
      }
    }

  }


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