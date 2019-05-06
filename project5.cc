#include "graph.cc"
#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <map>
#include <vector>

// Main function
int main()
{
  Graph graph;
  
  while (true)
  {
    // Check for eof and exit if so
    char c;
    std::cin >> c;
    if (std::cin.eof())
        break;
    else
        std::cin.unget();
  
    while ((!eof(std::cin))
    {
        readFile(std::cin);
        print();
    }
  }
}
