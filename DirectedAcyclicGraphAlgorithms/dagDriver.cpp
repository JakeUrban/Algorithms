#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <climits>
#include "headers/topologicalSort.h"
#include "headers/shortestPath.h"
#include "headers/longestPath.h"
#include "headers/numberOfPaths.h"
using namespace std;

int main() {
  
  int numOfGraphs;

  string line;
  getline(cin, line);
  numOfGraphs = atoi(line.c_str());
  
  for(int y = 0; y < numOfGraphs; y++) {
    cout << "Graph number: " << y+1 << endl;
    getline(cin, line);
    int numOfNodes = atoi(line.c_str());

    getline(cin, line);
    int numOfEdges = atoi(line.c_str());

    list<int> *aList = new list<int>[numOfNodes];
    for(int x = 0; x < numOfEdges; x++) {
      getline(cin, line);
      string buf, from, to;
      stringstream ss(line);
      while(ss >> buf) {
        if(from.empty()) {
          from = buf;
        }
        else {
          to = buf;
        }
      }
      int i = atoi(from.c_str());
      int j = atoi(to.c_str());
      aList[i-1].push_back(j);
    }

    ShortestPath spath(aList, numOfNodes);
    spath.execute();

    LongestPath lpath(aList,numOfNodes);
    lpath.execute();

    NumOfPaths numOfPaths(aList, numOfNodes);
    numOfPaths.execute();

    cout << endl;
    delete[] aList;
  }
  return 0;
}
