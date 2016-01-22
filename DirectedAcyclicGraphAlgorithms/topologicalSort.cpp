#include "headers/topologicalSort.h"

Sorter::Sorter(list<int> *l, int v) {
    alist = l;
    this->v = v;
    marked = new bool[v];
    for(int i = 0; i < v; i++) {marked[i] = false;}
}

list<int>* Sorter::topologicalSort() {
    for (int i = 0; i < v; i++) {
        if (marked[i] == false) {
            dfs(i);
        }
    }
    order.reverse();
    return &order;
}

void Sorter::dfs(int i) {
    marked[i] = true;
    list<int>::iterator it;
    for(it = alist[i].begin(); it != alist[i].end(); it++) {
        if(!marked[*it-1]) {
            dfs(*it-1);
        }
    }
    order.push_back(i+1);
}
