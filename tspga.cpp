#include "tspga.h"

#include<algorithm>
#include<iostream>
#include<time.h>

bool myCompare(const pair<int, double> a, const pair<int, double> b)
{
    return a.second < b.second;
}

int iRand(int fmin, int fmax)
{
    double f = (double) rand() / RAND_MAX;
    int result = (int) (fmin + f * (fmax - fmin) + 0.5);
    if(result < fmin || result > fmax)
    {
        cerr << endl << "Error! iRand result is not in range of " << fmin << ", " << fmax << endl;
    }
    return result;
}

vector<pair<int, int> > vectorDiff(vector<int> b, vector<int> a)
{
    vector<pair<int, int> > result;
    vector<int> c = a;
    for(unsigned int i = 0; i < b.size(); i++)
    {
        unsigned int j = find(c.begin(), c.end(), b[i]) - c.begin();
        if(i == j)
            continue;
        result.push_back(make_pair(i, j));
        iter_swap(c.begin() + i, c.begin() + j);
    }
    return result;
}

vector<int> vectorApplyDiff(vector<int> a, vector<pair<int, int> > diff, int startIndex, int endIndex)
{
    if(endIndex == -1)
        endIndex = diff.size();

    for(int i = startIndex; i < endIndex; i++)
        iter_swap(a.begin() + diff[i].first, a.begin() + diff[i].second);
    return a;
}

TSPGA::TSPGA(unsigned int numberOfPopulation, unsigned int numberOfGenerations, Graph g)
{
    this->g = g;
    this->numberOfGenerations = numberOfGenerations;
    population = vector<vector<int> >(numberOfPopulation, vector<int>(g.size() - 1));
}

double TSPGA::fitness(vector<int> x, int verbose)
{
    double dist = g.distance(0, x[0]);
    if(verbose) cout << "distances: 0-" << x[0] << "(" << g.distance(0, x[0]) << ")" << ", ";
    for(unsigned int i = 0; i < x.size() - 1; i++)
    {
        dist += g.distance(x[i], x[i + 1]);
        if(verbose) cout << x[i] << "-" << x[i + 1] << "(" << g.distance(x[i], x[i + 1]) << ")" << ", ";
    }
    dist += g.distance(x[x.size() - 1], 0);
    if(verbose)
    {
        cout << x[x.size() - 1] << "-0" << "(" << g.distance(x[x.size() - 1], 0) << ")" << ", ";
        cout << " --- sum: " << dist;
        cout << endl;
    }
    return dist;
}

void TSPGA::calculateFitnesses()
{
    sumFitness = 0;
    fitnesses.clear();
    for(unsigned int i = 0; i < population.size(); i++)
    {
        double f = fitness(population[i]);
        fitnesses.push_back(make_pair(i, f));
        sumFitness += 1000000 / f;
        if(f < fgbest || fgbest == -1)
        {
            f = fitness(population[i], 1);
            fgbest = f;
            gbest = vector<int>(population[i]);
            cout << "fgbest is changed:" << fgbest << endl;
            showVector(gbest);
        }
    }
    //std::sort(fitnesses.begin(), fitnesses.end(), myCompare);
}

vector<int> TSPGA::solve()
{
    firstGeneration();
    for(unsigned int i = 0; i < numberOfGenerations; i++)
    {
        calculateFitnesses();
        vector<vector<int> > newGeneration;
        for(unsigned int j = 0; j < population.size() / 2 - 1; j++)
        {
            pair<int, int> parent = naturalSelection();
            pair<vector<int>, vector<int> > children;
            children = crossover(parent);
//            children.first = population[j * 2];
//            children.second = population[j * 2 + 1];

            mutate(children.first);
            mutate(children.second);
            newGeneration.push_back(children.first);
            newGeneration.push_back(children.second);
        }
        vector<int> mutatedBestKnown = gbest;
        mutate(mutatedBestKnown, 1);
        newGeneration.push_back(gbest);
        newGeneration.push_back(mutatedBestKnown);

        population = vector<vector<int> >(newGeneration);
    }
    return gbest;
}

void TSPGA::firstGeneration()
{
    srand(time(NULL));
    for(unsigned int i = 0; i < population.size(); i++)
    {
        for(unsigned int j = 1; j <= population[i].size(); j++)
            population[i][j - 1] = j;
        showVector(population[i]);
        std::random_shuffle(population[i].begin(), population[i].end());
        showVector(population[i]);;

    }
    fgbest = -1;
}

int TSPGA::parentNaturalSelection()
{
    double agg = 0, randomParent = iRand(0, sumFitness);

    for(unsigned int i = 0; i < fitnesses.size(); i++)
    {
        if(agg + 1000000 / fitnesses[i].second > randomParent)
            return i;
        agg += 1000000 / fitnesses[i].second;
    }
    return fitnesses.size() - 1;
}

pair<int, int> TSPGA::naturalSelection()
{
    int p1 = parentNaturalSelection(), p2;
    while((p2 = parentNaturalSelection()) == p1);
    return make_pair(p1, p2);
}

pair<vector<int>, vector<int> > TSPGA::crossover(pair<int, int> parent)
{
    vector<pair<int, int> > diff = vectorDiff(population[parent.second], population[parent.first]);
    if(diff.size() <= 1)
    {
        return make_pair(population[parent.first], population[parent.second]);
    }
    unsigned int crosspoint = iRand(1, diff.size() - 1);
    if(crosspoint <= 0 || crosspoint >= diff.size())
        crosspoint = 1;
    pair<vector<int>, vector<int> > result;
    result.first = vectorApplyDiff(population[parent.first], diff, 0, crosspoint);
    result.second = vectorApplyDiff(population[parent.first], diff, crosspoint);
    return result;
}

bool TSPGA::mutate(vector<int> &x, double probability)
{
    if((double) rand() / RAND_MAX > probability)
        return false;
    int a = (int) iRand(0, x.size() - 1);
    int b;

    do{
        b = (int) iRand(0, x.size() - 1);
    }while(b == a);

    iter_swap(x.begin() + a, x.begin() + b);
    return true;
}

void showVector(vector<int> v, string name)
{
    if(name != "")
        cout << name << ": ";
    for(unsigned int i = 0; i < v.size(); i++)
    {
        if(i != 0)
            cout << ", ";
        cout << v[i];
    }
    cout << endl;
}
