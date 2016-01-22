#include <iostream>
#include "headers/numberOfPaths.h"
#include "headers/topologicalSort.h"

NumOfPaths::NumOfPaths(list<int> *l, int v) {
      alist = l;
      this->v = v;
}
void NumOfPaths::execute() {
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