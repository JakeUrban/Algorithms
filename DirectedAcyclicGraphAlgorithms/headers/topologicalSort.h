#ifndef TOPOLOGICALSORT_H
#define TOPOLOGICALSORT_H
#include <list>
using namespace std;

class Sorter {
  public:
    Sorter(list<int> *l, int v);
    list<int>* topologicalSort();
    void dfs(int i);

  private:
    list<int> *alist;
    bool *marked;
    list<int> order;
    int v;
};

#endif