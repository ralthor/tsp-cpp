#ifndef TSPGA_H
#define TSPGA_H

#include<string>
#include<vector>
#include "graph.h"

vector<pair<int, int> > vectorDiff(vector<int> b, vector<int> a);
vector<int> vectorApplyDiff(vector<int> a, vector<pair<int, int> > d, int startIndex = 0, int endIndex = -1);
void showVector(vector<int> v, string name = "");

class TSPGA
{
    public:
        TSPGA(unsigned int numberOfPopulation, unsigned int numberOfGenerations, Graph g);
        double fitness(vector<int> x, int verbose = 0);
        vector<int> solve();

    private:
        Graph g;
        unsigned int numberOfGenerations;
        vector<vector<int> > population;
        vector<int> gbest;
        vector<pair<int, double> > fitnesses;
        double sumFitness;
        double fgbest;

        void firstGeneration();
        void calculateFitnesses();
        pair<int, int> naturalSelection();
        int parentNaturalSelection();
        pair<vector<int>, vector<int> > crossover(pair<int, int> parent);
        vector<int> crossoverNext(pair<int, int> parent, int direction);
        bool mutate(vector<int> &x, double probability = 0.02);

};

#endif // TSPGA_H
