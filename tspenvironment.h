#ifndef TSPENVIRONMENT_H
#define TSPENVIRONMENT_H

#include "graph.h"

class TSPEnvironment
{
    public:
        TSPEnvironment(Graph g);
        virtual ~TSPEnvironment();
        void randomize();
        int fitness(vector<int> x);
        double solve();
    private:
        Graph graph;
        std::vector<std::vector<int> > x;
        std::vector<std::vector<int> > velocity;
        std::vector<std::vector<int> > pbest;
        std::vector<int> gbest;
        void calculateNewVelocities();
        void updateValues();
};

#endif // TSPENVIRONMENT_H
