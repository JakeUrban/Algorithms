#include <iostream>
#include "headers/longestPath.h"
#include "headers/topologicalSort.h"

LongestPath::LongestPath(list<int> *l, int v) {
      alist = l;
      numOfNodes = v;
}

void LongestPath::execute() {
      Sorter sorter(alist, numOfNodes);
      list<int> tOrder = *(sorter.topologicalSort());
    //Creating structure to list all inbound edges for each vertex
      list<int> *inList = new list<int>[numOfNodes];
      list<int>::iterator i;
      for(int j = 0; j < numOfNodes; j++) {
        for(i = alist[j].begin(); i != alist[j].end(); i++) {
          inList[*i-1].push_back(j+1);
        }
      }
    //Create structure to define longest path from 1 to dist[i]
      int dist[numOfNodes];
      int longestPath = 0;
    //Determine dist[v] for all v, and select max(dist[1...n]) 
      for(i = tOrder.begin(); i != tOrder.end(); i++) {
        if(inList[*i-1].size() == 0) {
          dist[*i-1] = 0;
        } 
        else {
          int maxDist = 0;
          for(list<int>::iterator j = inList[*i-1].begin(); j != inList[*i-1].end(); j++) {
            if(dist[*j-1] > maxDist) {
              maxDist = dist[*j-1];
            }
          }
          dist[*i-1] = maxDist + 1;
        }
      }//Longest path computed. Find it in dist[]
      for(int i = 0; i < numOfNodes; i++) {
        if(dist[i] > longestPath) {
          longestPath = dist[i];
        }
      }
      cout << "Longest Path: " << longestPath << endl;
      delete [] inList;
    }