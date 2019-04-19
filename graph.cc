#include <iostream>
#include <map>
#include <list>
#include <queue>
#include "graph.h"
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;


void bfs(int **matrix, int start, int numT, string list, ostream & output)
{
  // Mark all the vertices as unvisited
  bool visited [numT];
  for (int i = 0; i < numT; i++)
      visited[i] = false;

  // Create a queue
  queue<int> toVisit;
  toVisit.push(start);
  visited[start] = true;

  while (!toVisit.empty())
  {
    int curr = toVisit.front();
    toVisit.pop();
    //RT If you have an argument for where the output should go, use it.
    // cout << list[curr] << endl;   // Could happen before popping
    output << list[curr] << endl;   // Could happen before popping

    for (int i = 0; i < numT; i++)
    {
      if (matrix[curr][i] != 0 && (!visited[i]))
      {
        toVisit.push(i);
        visited[i] = true;
      }
    }
  }
}

int main()
{
  int numT;
  int numR;

  //RT These data structures (tMap, tList, rMatrix, bMatrix) need
  //   comments explaining them.  They probably belong in the Graph
  //   class, since it looks like they store the graph of towns and
  //   roads.
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
  //RT: The output should all go to cout, which is simpler.
  // filebuf output;
  // ostream os(&output);
  // bfs(rMatrix, 0, numT, tList, output);
  bfs(rMatrix, 0, numT, tList, cout);
  //RT: There's a second problem here.  You've created a fixed-sized
  //    2-D array, with the right size at runtime, but you can't pass
  //    that to a method, because the method can't know at compile-time
  //    what size the array will be.  I'd suggest using a vector, instead,
  //    because its size is adjustable at run-time.
  //
  //    On the other hand, if the array were inside the Graph class,
  //    then it wouldn't need to be an argument.

  return 0;
  // cout << "There are " << numT << " number of towns in the province, and " <<
  //    numR << " number of road(s)." << endl;

};
