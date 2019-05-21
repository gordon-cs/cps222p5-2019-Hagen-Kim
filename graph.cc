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

// Operate BFS traversal
void Graph::BFS()
{
  cout << "The input data is: " << endl;
  queue<Vertex*> traversal;
  vector<Vertex*> belong;
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
    for (size_t i = 0; i < vEdges.size(); i++)
    {
      //RT fix output
      cout << "    " << vEdges[i]->getOppositeVertex(current)->getName()
           << " " << vEdges[i]->getWeight() << " mi";

      if (vEdges[i]->isBridge())
      {
        cout << " via bridge";
//RT        cout << endl;
      }
      cout << endl; //RT fix output
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
  Vertex* currentVertex;
  queue<Vertex*> toVisit;
  vector<Vertex*> belong;
  //checks each vertex to locate the smallest one to take
  for (size_t i = 0; i < _vertices.size(); i++)
  {
      currentVertex = _vertices[i];
      currentVertex->updateWeight(std::numeric_limits<double>::max()); // Set the weight to max
      currentVertex->updatePredVertex(NULL);  //sets all the vertices to have no predecessor
  }

  _capital -> updateWeight(0);
  toVisit.push(_capital);
  while (!toVisit.empty())
  {
    currentVertex = toVisit.front();
    belong.push_back(currentVertex);
    vector<Edge*> adjEdges = currentVertex->getEdges();
    Vertex* adjVertex;
    for (size_t i = 0; i < adjEdges.size(); i++)
    {
      adjVertex = adjEdges[i]->getOppositeVertex(currentVertex);
      bool found = doesBelong(belong, adjVertex);
      if (!found)
      {
        toVisit.push(adjVertex);
        belong.push_back(adjVertex);
        double altWeight = currentVertex->getWeight() + adjEdges[i]->getWeight();
        if (altWeight < adjVertex->getWeight())
        {
          adjVertex->updateWeight(altWeight);
          adjVertex->updatePredVertex(currentVertex);
        }
      }
    }
    toVisit.pop();
  }
}

// Shortest route from capital to a vertex
void Graph::shortestPath(Vertex* v)
{
  //RT fix output
  cout << "      The shortest path from " << _capital->getName() << " to "
       << v->getName() << " is " << v->getWeight() << " mi:" << endl;
  stack<Vertex*> visitedVertices;
  Vertex* current = v;
  visitedVertices.push(current);
  while(current->getName() != _capital->getName())
  {
    visitedVertices.push(current->getPredVertex());
    current = current->getPredVertex();
  }
  while (!visitedVertices.empty())
  {
    cout << "\t\t" << visitedVertices.top()->getName() << endl;
    visitedVertices.pop();
  }
}

// Print the shortest path
void Graph::printShortestPath()
{
  std::cerr << "calling dijkstra" <<endl; //RT
  Dijkstra();
  std::cerr << "returned from dijkstra" <<endl; //RT
  //RT fix output
  cout << "The shortest paths from " << _capital->getName() << " are:" << endl;
  for (size_t i = 1; i < _vertices.size(); i++)
  {
    shortestPath(_vertices[i]);
  }
  std::cerr << "printShortestPath() returning" <<endl; //RT
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

    for (size_t i = 0; i < belong.size(); i++)
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
  std::cerr << "minSpanTree() returning" <<endl; //RT
  return spanningTree;
}

// Print the minimum spanning tree
void Graph::printMinSpanTree(vector<Edge*> e)
{
  cout << "The road upgrading goal can be achieved at minimal cost by upgrading: " << endl;
  for (size_t i = 0; i < e.size(); i++)
  {
    cout << "\t" << e[i]->getCityOne()->getName() << " to " << e[i]->getCityTwo()->getName() << endl;
  }
}

//Connected Components Algorithm to list vertices when bridges fail
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
      for (size_t i = 0; i < vEdges.size(); i++)
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
    size_t index = 0;
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

// Depth-first search traversal to visit all vertices
bool Graph::DFS(Vertex* v, vector<Vertex*> &visitedVertex, vector<Edge*> &treeEdges)
{
  vector<Edge*> adjEdges = v->getEdges();
  for (size_t i = 0; i < adjEdges.size(); i++)
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
  for (size_t i = 0; i < visitedVertex.size(); i++)
  {
    lows[i] = i;
  }
  Vertex* currentVertex;
  for (size_t i = visitedVertex.size() - 1; i >= 0; i--)
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
  for (size_t i = 0; i < visitedVertex.size(); i++)
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
  for (size_t i = 0; i < articulationPoints.size(); i++)
  {
    cout << "\t" << articulationPoints[i]->getName() << endl;
  }
  if (articulationPoints.empty())
  {
    cout << "\tNONE" << endl;
  }
}

// Return vertices or towns
vector<Vertex*> Graph::getVertices()
{ return _vertices; }

// Return edges or roads
vector<Edge*> Graph::getEdges()
{ return _edges; }

// Return capital
Vertex* Graph::getCapital()
{ return _capital; }

// Find vertex
Vertex* Graph::findVertex(string name)
{
  bool found = false;
  int index = 0;
  while (!found)
  {
    if (_vertices[index]->getName() == name)
      found = true;
    else
      index++;
  }
  return _vertices[index];
}

// Get the position of a vertex
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

// Boolean to check if a vertex is seen
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

// Boolean to check if an edge is a tree
bool Graph::isTreeEdge(Edge* e, vector<Edge*> treeEdges)
{
  for (size_t i = 0; i < treeEdges.size(); i++)
  {
    if (e == treeEdges[i])
      return true;
  }
  return false;
}

// Compare weights of edges between the capital and vertices
bool Graph::verticesWeightComparator::operator()(Vertex* a, Vertex* b)
{ return a->getWeight() > b->getWeight(); }

// Compare weights of edges
bool Graph::edgesWeightComparator::operator()(Edge* a, Edge* b)
{ return a->getWeight() > b->getWeight(); }


// Define constructor of class Vertex
Vertex::Vertex(string name)
: _name(name)
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

// Get the predecessor vertex
Vertex* Vertex::getPredVertex()
{ return _predVertex; }

// Get weight
double Vertex::getWeight()
{ return _weight; }

// Boolean to check if a vertex is adjacent
bool Vertex::isAdjacent(Vertex* v)
{
  for (size_t i = 0; i < _edges.size(); i++)
  {
    if (_edges[i]->getOppositeVertex(v)->getName() == _name)
      return true;
  }
  return false;
}

// Update the predecessor vertex
void Vertex::updatePredVertex(Vertex* v)
{ _predVertex = v; }

// Update the weight
void Vertex::updateWeight(double weight)
{ _weight = weight; }


// Define constructor of class Edge
Edge::Edge(Vertex* city1, Vertex* city2, bool bridge, double weight)
: _city1(city1), _city2(city2), _bridge(bridge), _weight(weight)
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
