#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H
#include <list>
using namespace std;

class ShortestPath {
  public:
    ShortestPath(list<int> *l, int v );
    void execute();

  private:
    list<int> *alist;
    int v;
};

#endif