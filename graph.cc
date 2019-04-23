/*
 * Project 5
 * Jenny and FeiFei
 * Got help from Jahnuel
 *
 */

#include <iostream>
#include <map>
#include <list>
#include <queue>
#include "graph.h"
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;


void bfs()
{
  // Mark all the vertices as unvisited
  bool visited [numT];
  for (int i = 0; i < numT; i++)
      visited[i] = false;

  // Create a queue
  queue<int> toVisit;
  toVisit.push(0);
  visited[0] = true;

  while (!toVisit.empty())
  {
    int curr = toVisit.front();
    toVisit.pop();
    cout << list[curr] << endl;   // Could happen before popping

    for (int j = 0; j < numT; j++)
    {
      if (matrix[curr][j] != 0 && (!visited[j]))
      {
        toVisit.push(j);
        visited[j] = true;
      }
    }
  }
}

int main()
{
  int numT;
  int numR;

  map<string, int> tMap;
  list<string> tList;

  cin >> numT, numR;

  int rMatrix[numT][numT];
  int bMatrix[numT][numT];

  for (int i = 0; i <= numT; i++)
  {
    string Town;
    cin >> Town;
    tList.push_back(Town);
    tMap.insert(pair<string, int> (Town, i));
  }

  for (int j = 0; j <= numR; j++)
  {
    string Town1;
    string Town2;
    char Bridge;
    int Road;
    int index1;
    int index2;

    cin >> Town1;
    cin >> Town2;
    cin >> Bridge;
    cin >> Road;

    index1 = tMap[Town1];
    index2 = tMap[Town2];

    if (Bridge == 'N')
      bMatrix[index1][index2] = 0;
    else
      bMatrix[index1][index2] = 1;

    rMatrix[index1][index2] = Road;
  }

  cout << "The input data is: " << endl;
  filebuf output;
  ostream os(&output);
  bfs(rMatrix, 0, numT, tList, output);

  return 0;
  // cout << "There are " << numT << " number of towns in the province, and " <<
  //    numR << " number of road(s)." << endl;

};
