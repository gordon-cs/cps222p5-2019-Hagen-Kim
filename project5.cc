#include "graph.h"
#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <map>
#include <vector>

// Main function
int main(int argc, char *argv[])
{
  while (!std::cin.eof())
  {
    int numOfVertices;
    std::cin >> numOfVertices;
    int numOfEdges;
    std::cin >> numOfEdges;
    vector<Vertex*> vertices;
    vector<Edge*> edges;
    Vertex* v = NULL;

    for (int i = 0; i < numOfVertices; i++)
    {
        string name;
        std::cin >> name;
        v = new Vertex(name);
        vertices.push_back(v);
    }

    for (int i = 0; i < numOfEdges; i++)
    {
        string city1;
        std::cin >> city1;
        string city2;
        std::cin >> city2;
        bool found = false;
        int index = 0;
        while (!found)
        {
            if (vertices[index]->getName() == city1)
                found = true;
            else 
                index++;
        }

        Vertex* cityOne = vertices[index];
        found = false;
        index = 0;
        while (!found)
        {
            if (vertices[index]->getName() == city2)
                found = true;
            else 
                index++;
        }

        Vertex* cityTwo = vertices[index];
        char bridgeFlag;
        bool isBridge;
        std::cin >> bridgeFlag;
        if (bridgeFlag == 'B')
            isBridge = true;
        else 
            isBridge = false;
        double weight;
        std::cin >> weight;
        Edge* e = new Edge(cityOne, cityTwo, isBridge, weight);
        edges.push_back(e);
    }
    
    for (int i = 0; i < numOfEdges; i++)
    {
        Edge* theEdge = edges[i];
        theEdge->getCityOne()->addEdge(theEdge);
        theEdge->getCityTwo()->addEdge(theEdge);
    }
    Vertex* capital = vertices[0];
    Graph g(vertices, edges, capital);
    g.BFS();
    g.printShortestPath();
    g.printMinSpanTree(g.minSpanTree());
    g.connectedComponents();
    g.articulationPoints();
    cout << "----------------------------------------------" << endl;

    // Check for eof and exit if so
    char c;
    std::cin >> c;
    if (std::cin.eof())
        break;
    else
        std::cin.unget();
    }
    return 0;
}
