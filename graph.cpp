#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include "graph.h"

#define MY_BIG_INT 100000000

Graph::Graph()
{
    //ctor
}

Graph::Graph(int n)
{
    dist = vector<vector<int> > (n, vector<int>(n, -1));
}

Graph::Graph(string filename)
{
    ifstream fin(filename.c_str());
    int n;
    fin >> n;
    dist = vector<vector<int> > (n, vector<int>(n, -1));
    vector<pair<int, int> > coord;
    for(int i = 0; i < n; i++)
    {
        int node, x, y;
        fin >> node >> x >> y;
        coord.push_back(make_pair<int&, int&>(x, y));
    }
    fin.close();
    for(int i = 0; i < n; i++)
        for(int j = 0; j <= i; j++)
        {
            dist[i][j] = int_distance(coord[i], coord[j]);
            dist[j][i] = dist[i][j];
        }
}

Graph::~Graph()
{
    //dtor
}

int Graph::distance(unsigned int a, unsigned int b)
{
    if(a <= 0 && b <= 0)
        return MY_BIG_INT;
    if(a < 0)
        a = 0;
    if(b < 0)
        b = 0;
    if(a >= dist.size() || b >= dist[0].size())
        return MY_BIG_INT;
    return dist[a][b];
}

int Graph::size()
{
    return dist.size();
}

int int_distance(pair<int, int> a, pair<int, int> b)
{
    int dx = a.first - b.first;
    int dy = a.second - b.second;
    float result = sqrt(dx * dx + dy * dy);
    return (int) (result + 0.5);
}
