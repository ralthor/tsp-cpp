#ifndef MY_GRAPH_H
#define MY_GRAPH_H

#include <vector>
#include <string>

using namespace std;

int int_distance(pair<int, int> a, pair<int, int> b);

class Graph
{
    public:
        Graph();
        Graph(int n);
        Graph(string filename);
        ~Graph();
        int distance(unsigned int a, unsigned int b);
        int size();

    private:
        vector<vector<int> > dist;
};

#endif // MY_GRAPH_H
