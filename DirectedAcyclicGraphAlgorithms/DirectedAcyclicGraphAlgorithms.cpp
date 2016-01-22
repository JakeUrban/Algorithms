/*
This program takes in directed acyclic graph information from stdin and performs several algorithms.
*/
#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <climits>
using namespace std;

class Sorter {
  public:
    Sorter(list<int> *l, int v) {
      alist = l;
      this->v = v;
      marked = new bool[v];
      for(int i = 0; i < v; i++) {marked[i] = false;}
    }

    list<int>* topologicalSort() {
      for (int i = 0; i < v; i++) {
        if (marked[i] == false) {
          dfs(i);
        }
      }
      order.reverse();
      return &order;
    }

    void dfs(int i) {
      marked[i] = true;
      list<int>::iterator it;
      for(it = alist[i].begin(); it != alist[i].end(); it++) {
        if(!marked[*it-1]) {
          dfs(*it-1);
        }
      }
      order.push_back(i+1);
    }

  private:
    list<int> *alist;
    bool *marked;
    list<int> order;
    int v;
};

class LongestPath {
  public:
    LongestPath(list<int> *l, int v) {
      alist = l;
      numOfNodes = v;
    }
    void execute() {
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
  private:
    list<int> *alist;
    int numOfNodes;
};

class ShortestPath {
  public:
    ShortestPath(list<int> *l, int v ) {
      alist = l;
      this->v = v;
    }
    void execute() {
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
  private:
    list<int> *alist;
    int v;
};

class NumOfPaths {
  public:
    NumOfPaths(list<int> *l, int v) {
      alist = l;
      this->v = v;
    }
    void execute() {
       Sorter sorter(alist,v);
       list<int> tOrder = *(sorter.topologicalSort());
     //Creating array for number of paths to destination for each vertex
       int numOfPaths[v];
       for(int i = 0; i < v; i++) {
         numOfPaths[i] = 0;
       }
     //Determining numOfPaths[i] for every vertex
       tOrder.reverse();
       list<int>::iterator i;
       for(i = tOrder.begin(); i != tOrder.end(); i++) {
         for(list<int>::iterator j = alist[*i-1].begin(); j != alist[*i-1].end(); j++) {
           if(numOfPaths[*j-1] == 0) {
             numOfPaths[*i-1] += 1;
           } 
           else {
             numOfPaths[*i-1] += numOfPaths[*j-1];
           }
         }
       }
       cout << "Number of Paths: " << numOfPaths[tOrder.back()-1] << endl;
    }
  private:
    list<int> *alist;
    int v;
};

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
