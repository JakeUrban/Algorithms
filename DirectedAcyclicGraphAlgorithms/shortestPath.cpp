#include <iostream>
#include <climits>
#include "headers/shortestPath.h"
#include "headers/topologicalSort.h"

ShortestPath::ShortestPath(list<int> *l, int v ) {
      alist = l;
      this->v = v;
}
void ShortestPath::execute() {
      Sorter sorter(alist,v);
      list<int> tOrder = *(sorter.topologicalSort());
      list<int>::iterator i;
    //Creating list of distances from source
      int distFromSource[v];
      for(int i = 0; i < v; i++) {
        distFromSource[i] = INT_MAX;
      }
      distFromSource[0] = 0;
    //Creating structure to list all inbound edges for each vertex
      list<int> *inList = new list<int>[v];
      for(int j = 0; j < v; j++) {
        for(i = alist[j].begin(); i != alist[j].end(); i++) {
          inList[*i-1].push_back(j+1);
        }
      }
    //Determining each vertex's shortest distance from source
      for(i = tOrder.begin(); i != tOrder.end(); i++) {
        if(inList[*i-1].size() == 0) {
          continue;
        }
        int minDist = INT_MAX;
        for(list<int>::iterator j = inList[*i-1].begin(); j != inList[*i-1].end(); j++) {
          if(distFromSource[*j-1] < minDist) {
            minDist = distFromSource[*j-1];
          }
        }
        distFromSource[*i-1] = minDist+1;
      }
      delete [] inList;
      cout << "Shortest Path: " << distFromSource[tOrder.back()-1] << endl;
}