/*
 * Project 5
 * Jenny and FeiFei
 * Got help from Jahnuel and Stephen to understand better
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
void Graph::BFS()
{  
  cout << "The input data is: " << endl;
  queue<Vertex*> traversal;
  vector<Vertex*> belog;
  traversal.push(_capital);
  Vertex *current;
  //while the queue of vertex pointers is not empty
  while(!traversal.empty())
  {
    //refers to first or the oldest element in the queue
    current = traversal.front();
    //pushes the current into a vector from the back
    belong.push_back(current);
    cout << current->getName() << endl;
    vector<Edge*> vEdges = current->getEdges();

    //checks each edge size to determine the length as well as if it is a bridge or not
    for (int i = 0; i < vEdges.size(); i++)
    {
      cout << "\t" << vEdges[i]->getOppositeVertex(current)->getName() << " " << vEdges[i]->getWeight() << " mi";

      if (vEdges[i]->isBridge())
      { 
        cout << " via bridge";
        cout << endl;
      }
      //boolean to check whether edge has been located 
      bool found = doesBelong(belong, vEdges[i]->getOppositeVertex(current));
      //if the opposite vertex is not found, then push to queue
      if (!found)
      {
        traversal.push(vEdges[i]->getOppositeVertex(current));
        belong.push_back(vEdges[i]->getOppositeVertex(current));
      }
    }

    traversal.pop();
  }
}

//Dijskra's Shortest Path Algorithm
void Graph::Dijkstra()
{
  Vertex* current;
  queue<Vertex*> toVisit;
  vector<Vertex*> belong;
  //checks each vertex to locate the smallest one to take
  for (int i = 0; i < _vertices.size(); i++) 
  {
      current = _vertices[i];
      //sets all of the vertices to be infinity
      current -> updatePredVertex(std::numeric_limits<double>::max());
      //sets all the vertices to have no predecessor
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

//Minimizing Spanning Tree Algorithm
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

//Connected Components Algorithm
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

bool Graph::DFS(Vertex* v, vector<Vertex*> &visitedVertex, vector<Edge*> &treeEdges)
{
  vector<Edge*> adjEdges = v->getEdges();
  for (int i = 0; i < adjEdges.size(); i++)
  {
    Edge* currentEdge = adjEdges[i];
    if (!doesBelong(visitedVertex, currentEdge->getOppositeVertex(v)))
    {
      treeEdges.push_back(adjEdges[i]);
      visitedVertex.push_back(currentEdge->getOppositeVertex(v));
      DFS(currentEdge->getOppositeVertex(v), visitedVertex, treeEdges);
    }
  }
  if (visitedVertex.size() == _vertices.size())
    return true;
  else 
    return false;
}

//Articulation Points Algorithm
void Graph::articulationPoints()
{
  vector<Vertex*> visitedVertex;
  vector<Edge*> treeEdges;
  visitedVertex.push_back(_capital);
  DFS(_capital, visitedVertex, treeEdges);
  int lows[visitedVertex.size()];
  for (int i = 0; i < visitedVertex.size(); i++)
  {
    lows[i] = i;
  }
  Vertex* currentVertex;
  for (int i = visitedVertex.size() - 1; i >= 0; i--)
  {
    currentVertex = visitedVertex[i];
    vector<Edge*> adjEdges = currentVertex->getEdges();
    int DFSPosition = getVertexPosition(currentVertex, visitedVertex);
    for (int j = 0; j < adjEdges.size(); j++)
    {
      if (!isTreeEdge(adjEdges[j], treeEdges))
      {
        int backedgeVertex = getVertexPosition(adjEdges[j]->getOppositeVertex(currentVertex), visitedVertex);
        if (backedgeVertex < lows[DFSPosition])
          lows[DFSPosition] = backedgeVertex;
      }
      else 
      {
        if (getVertexPosition(adjEdges[j]->getOppositeVertex(currentVertex), visitedVertex) > getVertexPosition(currentVertex, visitedVertex))
        {
          if (lows[getVertexPosition(adjEdges[j]->getOppositeVertex(currentVertex), visitedVertex)] <= lows[i])
          {
            lows[i] = lows[getVertexPosition(adjEdges[j]->getOppositeVertex(currentVertex), visitedVertex)];
          }
        }
      }
    }
  }
  vector<Vertex*> articulationPoints;
  int rootChild = 0;
  for (int i = 0; i < visitedVertex.size(); i++)
  {
    currentVertex = visitedVertex[i];
    vector<Edge*> adjEdges = currentVertex->getEdges();
    for (int j = 0; j < adjEdges.size(); j++)
    {
      int DFSPositionOpp = getVertexPosition(adjEdges[j]->getOppositeVertex(currentVertex), visitedVertex);
      if (i == 0 && isTreeEdge(adjEdges[j], treeEdges))
      {
        rootChild++;
      }
      if (DFSPositionOpp > i && isTreeEdge(adjEdges[j], treeEdges) && i != 0)
      {
        if (i <= lows[DFSPositionOpp] && !doesBelong(articulationPoints, currentVertex))
        {
          articulationPoints.push_back(currentVertex);
        }
      }
    }
  }
  if (rootChild > 1)
  {
    articulationPoints.push_back(_capital);
  }
  cout << "Obliterating any of the following would result in the province becoming disconnected: " << endl;
  for (int i = 0; i < articulationPoints.size(); i++)
  {
    cout << "\t" << articulationPoints[i]->getName() << endl;
  }
  if (articulationPoints.empty())
  {
    cout << "\tNONE" << endl;
  }
}

// Get vertex of a city
vector<Vertex*> Graph::getVertices()
{ return _vertices; }

vector<Edge*> Graph::getEdges()
{ return _edges; }

Vertex* Graph::getCapital()
{ return _capital; }

Vertex* Graph::findVertex(string name)
{
  bool found = false;
  int index = 0;
  while (!found)
  {
    if (_vertices[index]->getName() == name)
      found == true;
    else
      index++;
  }
  return _vertices[index];
}

int Graph::getVertexPosition(Vertex* v, vector<Vertex*> vertices)
{
  bool found = false;
  int index = 0;
  while (!found)
  {
    if (vertices[index] == v)
      found = true;
    else
      index++;
  }
  return index;
}

bool Graph::doesBelong(vector<Vertex*> belong, Vertex* v)
{
  bool found = false;
  int index = 0;
  while (!belong.empty() && index != belong.size())
  {
    if (belong[index]->getName() == v->getName())
    {
      index = belong.size();
      found = true;
    }
    else 
      index++;
  }
  return found;
}

bool Graph::isTreeEdge(Edge* e, vector<Edge*> treeEdges)
{
  for (int i = 0; i < treeEdges.size(); i++)
  {
    if (e == treeEdges[i])
      return true;
  }
  return false;
}

bool Graph::verticesWeightComparator::operator()(Vertex* a, Vertex* b)
{ return a->getWeight() > b->getWeight(); }

bool Graph::edgesWeightComparator::operator()(Edge* a, Edge* b)
{ return a->getWeight() > b->getWeight(); }


// Define constructor of class Vertex
Vertex::Vertex(string name)
: _name(name)
{ }

// Destructor of a class Vertex
Vertex::~Vertex()
{ }

// Get name of a vertex
string Vertex::getName()
{ return _name; }

// Get edges of a vertex
vector<Edge*> Vertex::getEdges()
{ return _edges; }

// Add an edge to the list of edges
void Vertex::addEdge(Edge* e)
{  _edges.push_back(e); }

Vertex* Vertex::getPredVertex()
{ return _predVertex; }

double Vertex::getWeight()
{ return _weight; }

bool Vertex::isAdjacent(Vertex* v)
{
  for (int i = 0; i < _edges.size(); i++)
  {
    if (_edges[i]->getOppositeVertex(v)->getName() == _name)
      return true;
  }
  return false;
}

void Vertex::updatePredVertex(Vertex* v)
{ _predVertex = v; }

void Vertex::updateWeight(double weight)
{ _weight = weight; }


// Define constructor of class Edge
Edge::Edge(Vertex* city1, Vertex* city2, bool bridge, double weight)
: _city1(city1), _city2(city2), _bridge(bridge), _weight(weight)
{ }

// Destructor of a class Edge
Edge::~Edge()
{ }

// Return name of city1
Vertex* Edge::getCityOne()
{ return _city1; }

// Return name of city2
Vertex* Edge::getCityTwo()
{ return _city2; }

// Return boolean checking edges as bridge
bool Edge::isBridge()
{ return _bridge; }

// Return weight of edges
double Edge::getWeight()
{ return _weight; }

Vertex* Edge::getOppositeVertex(Vertex* v)
{
  if (_city2->getName() != v->getName())
    return _city2;
  else 
    return _city1;
}
