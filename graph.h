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
#include <deque>
#include <queue>
#include <string>
#include <list>
#include <vector>
#include <stack>


class Edge
{
  public:

    /* Parameters: city1 -- initial point
     *             city2 -- final point
     *             bridge -- boolean to check if the edge is a bridge or not
     *             weight -- weight of the edge
     */
    Edge(std::string city1, std::string city2, bool bridge, int weight);
    ~Edge();
    std::string getCityOneName();
    std::string getCityTwoName(); 
    bool isEdgeBridge();        
    int getWeight();             

  private:

    std::string cityOne;
    std::string cityTwo;
    bool isBridge;
    int weightOfEdges;

};

class Vertex
{
  public:

    /* Parameters: name -- name of a vertex
     *             capital -- boolean to check if the vertex is a capital or not
     */
    Vertex(std::string name, bool capital);
    ~Vertex();

    std::string getName();              
    void addEdge(Edge *e);         
    std::vector<Edge *> getEdgeList();   
    bool isVertexCapital();       

  private:
    std::string cityName;
    bool isCapital;
    std::vector<Edge *> edges;
};

class Graph
{
  public:

    // Parameter: fileName -- A file of data
    Graph(std::string fileName);
    ~Graph();

    std::deque<Vertex *> getVertexList();       
    Vertex* getVertex(std::string citiesName);  
    void addVertex(Vertex *);             
    std::deque<std::string> BFS();  
    std::deque<std::string> Dijkstra();
    void shortestRoute();
    std::stack<std::string> DFS(int s);                  
    void print();                         
    void readFile();                        

  private:

    std::deque<Vertex *> vertices;
    std::string file;
    std::string cityNames;

};

#endif