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
Graph::Graph(vector<Vertex*> vertices, vector<Edge*> edges, Vertex* capital)
: _vertices(vertices), _edges(edges), _capital(capital)
{ }

// Destructor of class Graph
Graph::~Graph()
{ }

// Operate BFS traversal
/*
 * Jahnuel helped us by explaining more of what needed to be done for the BFS traversal function
 */
void Graph::BFS()
{  
  cout << "The input data is: " << endl;
  queue<Vertex*> traversal;
  vector<Vertex*> belog;
  traversal.push(_capital);
  Vertex *current;

  while(!traversal.empty())
  {
    current = traversal.front();
    belong.push_back(current);
    cout << current->getName() << endl;
    vector<Edge*> vEdges = current->getEdges();

    for (int i = 0; i < vEdges.size(); i++)
    {
      cout << "\t" << vEdges[i]->getOppositeVertex(current)->getName() << " " << vEdges[i]->getWeight() << " mi";

      if (vEdges[i]->isBridge())
      { 
        cout << " via bridge";
        cout << endl;
      }

      bool found = doesBelong(belong, vEdges[i]->getOppositeVertex(current));
      if (!found)
      {
        traversal.push(vEdges[i]->getOppositeVertex(current));
        belong.push_back(vEdges[i]->getOppositeVertex(current));
      }
    }

    traversal.pop();
  }
}

void Graph::Dijkstra()
{
  Vertex* current;
  queue<Vertex*> toVisit;
  vector<Vertex*> belong;

  for (int i = 0; i < _vertices.size(); i++) 
  {
      current = _vertices[i];
      current -> updatePredVertex(std::numeric_limits<double>::max());
      current -> updatePredVertex(NULL);
  }

  _capital -> updateWeight(0);
  toVisit.push(_capital);
  while (!toVisit.empty())
  {
    current = toVisit.front();
    belong.push_back(current);
    vector<Edge *> adjEdges = current -> getEdges();
    Vertex* adjVertex;
    for (int i = 0; i < adjEdges.size(); i++)
    {
      adjVertex = adjEdges[i] -> getOppositeVertex(current);
      bool has = doesBelong(belong, adjVertex);
      if (!has)
      {
        toVisit.push(adjVertex);
        belong.push_back(adjVertex);
        double altWeight = current -> getWeight() + adjEdges[i] -> getWeight();
        if (altWeight < adjVertex -> getWeight())
        {
          adjVertex -> updateWeight(alt);
          adjEdges -> updatePredVertex(current);
        }
      }
    }
    toVisit.pop();
  }
}

void Graph::shortestPath(Vertex *v)
{
  cout << "\tThe shortest route from " << _capital->getName() << " to " << v->getName()
      << " is " << v->getWeight() << " mi" << endl;
  stack <Vertex *> vertices;
  Vertex* current = v;
  vertices.push(current);
  while(current -> getName() != _capital -> getName())
  {
    vertices.push(current -> getPredVertex());
    current = current -> getPredVertex();
  }
  while (!vertices.empty())
  {
    cout << "\t\t" << vertices.top()->getName() << endl;
    vertices.pop();
  }
}

void Graph::printShortestPath()
{
  Dijkstra();
  cout << "The shortest routes from " << _capital->getName() << " are:" << endl;
  for (int i = 1; i < _vertices.size(); i++)
  {
    shortestPath(_vertices[i]);
  }
}

vector<Edge*> Graph::minSpanTree()
{
  vector<Edge*> spanningTree;
  vector<Vertex*> belong;
  Vertex* currentVertex = _capital;
  vector<Edge*> availableEdges;
  belong.push_back(_capital);
  Edge* smallestEdge;
  double minWeight;
  while(spanningTree.size() < _vertices.size() - 1)
  {
    minWeight = std::numeric_limits<double>::max();

    for (int i = 0; i < belong.size(); i++)
    {
      currentVertex = belong[i];
      availableEdges = currentVertex->getEdges();
      for (int j = 0; j < availableEdges.size(); j++)
      {
        if ((availableEdges[j]->getWeight() < minWeight) && (!isTreeEdge(availableEdges[j], spanningTree)) && (doesBelong(belong, availableEdges[j]->getOppositeVertex(currentVertex))))
        {
          smallestEdge = availableEdges[j];
          minWeight = availableEdges[j]->getWeight();
        }
      }
    }
    if (!isTreeEdge(smallestEdge, spanningTree))
    {
      spanningTree.push_back(smallestEdge);
    }
    belong.push_back(smallestEdge->getOppositeVertex(currentVertex));
  }
  return spanningTree;
}

void Graph::printMinSpanTree(vector<Edge*> e)
{
  cout << "The road upgrading goal can be achieved at minimal cost by upgrading: " << endl;
  for (int i = 0; i < e.size(); i++)
  {
    cout << "\t" << e[i]->getCityOne()->getName() << " to " << e[i]->getCityTwo()->getName() << endl;
  }
}

void Graph::connectedComponents()
{
  cout << "Connected components in event of a major storm are: " << endl;
  vector<Vertex*> visited;
  queue<Vertex*> vertices;
  vertices.push(_capital);
  while (visited.size() < _vertices.size())
  {
    cout << "\tIf all bridges fail, the following towns would form an isolated group: " << endl;
    vector<Vertex*> belong;
    Vertex* currentVertex;
    while (!vertices.empty())
    {
      currentVertex = vertices.front();
      belong.push_back(currentVertex);
      visited.push_back(currentVertex);
      vector<Edge*> vEdges = currentVertex->getEdges();
      for (int i = 0; i < vEdges.size(); i++)
      {
        if (!vEdges[i]->isBridge())
        {
          bool found = doesBelong(belong, vEdges[i]->getOppositeVertex(currentVertex));
          if (!found)
          {
            vertices.push(vEdges[i]->getOppositeVertex(currentVertex));
            belong.push_back(vEdges[i]->getOppositeVertex(currentVertex));
            if (!doesBelong(visited, currentVertex))
            {
              visited.push_back(currentVertex);
            }
          }
        }
      }
      cout << "\t\t" << vertices.front()->getName() << endl;
      vertices.pop();
    }
    bool done = true;
    int index = 0;
    while (done && index != _vertices.size())
    {
      bool found = false;
      int j = 0;
      while (!found && j != visited.size())
      {
        if (_vertices[index] == visited[j])
          found = true;
        else 
          j++;
      }
      if (!found)
      {
        done = false;
        vertices.push(_vertices[index]);
      }
      else 
        index++;
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
    else if (list.size() == 4)
    {
      std::string b = list.at(2);
      bool bridge = "false";

      if (b == "B")
        bridge = true;

      Edge *e = new Edge(list.at(0), list.at(1), bridge, stoi(list.at(3)));
      Vertex *v;
      std::vector<Edge *> edges = v -> getEdgeList();
      v = getVertex(list.at(0));
      v->addEdge(e);
      v = getVertex(list.at(1));
      v->addEdge(e);
      edges.push_back(e);
    }
    list.clear();
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