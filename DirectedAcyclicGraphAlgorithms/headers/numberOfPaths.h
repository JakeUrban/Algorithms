#ifndef NUMOFPATHS_H
#define NUMOFPATHS_H
#include <list>
using namespace std;

class NumOfPaths {
  public:
    NumOfPaths(list<int> *l, int v);
    void execute();

  private:
    list<int> *alist;
    int v;
};

#endif