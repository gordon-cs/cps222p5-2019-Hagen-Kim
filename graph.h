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

using namespace std;

class Edge
{
  public:

    /* Parameters: city1 -- initial point
     *             city2 -- final point
     *             bridge -- boolean to check if the edge is a bridge or not
     *             weight -- weight of the edge
     */
    Edge(string city1, string city2, bool bridge, int weight);
    ~Edge();
    string getCityOneName();
    string getCityTwoName(); 
    bool isEdgeBridge();        
    int getWeight();            

  private:

    string cityOne;
    string cityTwo;
    bool isBridge;
    int weightOfEdges;

};

class Vertex
{
  public:

    /* Parameters: name -- name of a vertex
     *             capital -- boolean to check if the vertex is a capital or not
     */
    Vertex(string name, bool capital);
    ~Vertex();

    string getName();              
    void addEdge(Edge *e);         
    vector<Edge *> getEdgeList();   
    bool isVertexCapital();       

  private:
    string cityName;
    bool isCapital;
    vector<Edge *> edges;
};

class Graph
{
  public:

    // Parameter: fileName -- A file of data
    Graph(string fileName);
    ~Graph();

    deque<Vertex *> getVertexList();       
    Vertex* getVertex(string citiesName);  
    void addVertex(Vertex *);             
    deque<string> BFS();                    
    void print();                         
    void readFile();                        

  private:

    deque<Vertex *> vertices;
    string file;
    string cityNames;

};

#endif