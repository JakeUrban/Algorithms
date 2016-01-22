#ifndef LONGESTPATH_H
#define LONGESTPATH_H
#include <list>
using namespace std;

class LongestPath {
  public:
    LongestPath(list<int> *l, int v);
    void execute();

  private:
    list<int> *alist;
    int numOfNodes;
};

#endif