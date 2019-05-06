/*
 * Project 5
 * Jenny and FeiFei
 * Got help from Jahnuel
 *
 */

#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stack>
#include <string>
#include <list>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::queue;
using std::vector;
using std::stack;

class Vertex;
class Edge;

class Vertex
{
  public:

    /* Constructor */
    Vertex(string name);
    ~Vertex();

    // Accessor for name of vertex
    string getName();   

    // Accessor for the list of edges    
    vector<Edge *> getEdges();   

    // Add an edge to the vertex's vector
    void addEdge(Edge *e);  
    
    // Accessor for predecessor vertex
    Vertex* getPredVertex();   

    // Accessor for weight
    double getWeight();

    // Boolean to check if a vertex is adjacent or not
    bool isAdjacent(Vertex* v);

    // Update predecessor vertex if shorter route is found
    void updatePredVertex(Vertex* v);

    // Update weight when necessary
    void updateWeight(double weight);

    

  private:

    // Instance variables
    string _name;
    vector<Edge *> _edges;
    Vertex* _predVertex;
    double _weight;
};

class Edge
{
  public:

    /* Constructor */
    Edge(Vertex* city1, Vertex* city2, bool bridge, double weight);
    ~Edge();

    // Accessor of city 1
    Vertex* getCityOne();

    // Accessor of city 2
    Vertex* getCityTwo(); 

    // Boolean to check if the edge is a bridge or not
    bool isBridge();        

    // Accessor for weight
    double getWeight(); 

    // Accessor for the opposite vertex
    Vertex* getOppositeVertex(Vertex* v);           

  private:

    // Instant variables
    Vertex* _city1;
    Vertex* _city2;
    bool _bridge;
    double _weight;

};

class Graph
{
  public:

    /* Constructor */
    Graph(vector<Vertex*> vertices, vector<Edge*> edges, Vertex* capital);
    ~Graph();

    // Traverse vertices by breadth-first search
    void BFS(); 

    // Dijkstra's algorithm to find shortest paths from capital
    void Dijkstra();

    // Find shortest path from the capital to a vertex
    void shortestPath(Vertex* v);

    // Print the shortest path
    void printShortestPath();

    // Create a minimum spanning tree
    vector<Edge*> minSpanTree();

    // Print the minimum spanning tree
    void printMinSpanTree(vector<Edge*> e);

    // Find the partitioned regions when bridges are destroyed by storm
    void connectedComponents();

    // Find articulation points
    void articulationPoints();

    // Traverse by depth-first search
    bool DFS(Vertex* v, vector<Vertex*> &visited, vector<Edge*> &treeEdges);

    // Accessor for vertices
    vector<Vertex*> getVertices();

    // Accessor for edges
    vector<Edge*> getEdges();

    // Accessor for capital
    Vertex* getCapital();

    // Accessor for a vertex given the name of city
    Vertex* findVertex(string name);                                   

  private:

    // Instance variables
    vector<Vertex*> _vertices;
    vector<Edge*> _edges;
    Vertex* _capital;

    // Get the position of a vertex
    int getVertexPosition(Vertex* v, vector<Vertex*> vertices);

    // Boolean to check if a given vertex is within a vector
    bool doesBelong(vector<Vertex*> belong, Vertex* v);

    // Boolean to check if a given edge is a tree edge
    bool isTreeEdge(Edge* e, vector<Edge*> treeEdges);

class verticesWeightComparator
{
  public:
    // Compare vertices based on their weights from the capital
    bool operator()(Vertex* a, Vertex* b);
};

class edgesWeightComparator
{
  public:
    //Compare edges based on their weights from one another
    bool operator()(Edge* a, Edge* b);
};

};

#endif