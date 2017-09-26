#include "tspga.h"

#include<algorithm>
#include<iostream>
#include<time.h>

bool myCompare(const pair<int, double> a, const pair<int, double> b)
{
    return a.second < b.second;
}

int iRand(int lowest, int highest)
{
    int random_integer;

    int range=(highest-lowest)+1;
    random_integer = lowest + int (range*(rand()/(RAND_MAX + 1.0)));
    return random_integer;
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
    population = vector<vector<int> >(numberOfPopulation, vector<int>(g.size()));
}

double TSPGA::fitness(vector<int> x, int verbose)
{
    double dist = 0;
    for(unsigned int i = 0; i < x.size() - 1; i++)
    {
        dist += g.distance(x[i], x[i + 1]);
        if(verbose) cout << x[i] << "-" << x[i + 1] << "(" << g.distance(x[i], x[i + 1]) << ")" << ", ";
    }
    dist += g.distance(x[x.size() - 1], x[0]);
    if(verbose)
    {
        cout << x[x.size() - 1] << "-" << x[0] << "(" << g.distance(x[x.size() - 1], x[0]) << ")" << ", ";
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

//            double m1 = fitness(population[parent.first]);
//            double m2 = fitness(population[parent.second]);
//            double k1 = fitness(children.first);
//            double k2 = fitness(children.second);
//            if(fgbest > k1 + k2 + m1 + m2)
//                cout << "hehe";

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
        for(unsigned int j = 0; j < population[i].size(); j++)
            population[i][j] = j;
//        showVector(population[i]);
        std::random_shuffle(population[i].begin(), population[i].end());
//        showVector(population[i]);;

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
    pair<vector<int>, vector<int> > result;
    result.first = crossoverNext(parent, 1);
    result.second = crossoverNext(parent, -1);
    return result;
}

int nextNode(vector<int> &vect, int x)
{
    unsigned int position = std::find(vect.begin(), vect.end(), x) - vect.begin();
    int result;
    if(position == vect.size() - 1)
        result = vect[0];
    else
        result = vect[position + 1];

    vect.erase(vect.begin() + position);

    return result;
}

int previousNode(vector<int> &vect, int x)
{
    unsigned int position = std::find(vect.begin(), vect.end(), x) - vect.begin();
    int result;
    if(position == 0)
        result = vect[vect.size() - 1];
    else
        result = vect[position - 1];

    vect.erase(vect.begin() + position);

    return result;
}

vector<int> TSPGA::crossoverNext(pair<int, int> parent, int direction)
{
    vector<int> result;
    vector<int> parentX(population[parent.first]);
    vector<int> parentY(population[parent.second]);

    int candidateX, candidateY;
    int crosspoint = iRand(0, parentX.size() - 1);
    int c = parentX[crosspoint];
    result.push_back(c);
    while(parentX.size() > 1)
    {
        int distX, distY;
        if(direction == 1)
        {
            candidateX = nextNode(parentX, c);
            candidateY = nextNode(parentY, c);
            distX = g.distance(c, candidateX);
            distY = g.distance(c, candidateY);
        }
        else
        {
            candidateX = previousNode(parentX, c);
            candidateY = previousNode(parentY, c);
            distX = g.distance(candidateX, c);
            distY = g.distance(candidateY, c);
        }
        if(distX < distY)
            c = candidateX;
        else
            c = candidateY;
        result.push_back(c);
    }
    return result;
}

vector<int>mySlice(vector<int> vect, int from, int to)
{
  vector<int>::iterator first = vect.begin() + from;
  vector<int>::iterator last  = vect.begin() + to;
  return vector<int>(first, last);
}

vector<int> concat(vector<int> a, vector<int> b)
{
    a.insert(a.end(), b.begin(), b.end());
    return a;
}

bool TSPGA::mutate(vector<int> &a, double probability)
{
    if((double) rand() / RAND_MAX > probability)
        return false;
    int m,n;
    do {
        m = iRand(0, a.size() / 2);
        n = iRand(0, a.size() - 1);
    } while (m>=n);
    vector<int> s1 = mySlice(a, 0, m);
    vector<int> s2 = mySlice(a, m, n);
    vector<int> s3 = mySlice(a, n, a.size());

    s1 = concat(s2, s1);
    a = concat(s1, s3);
//    int a = (int) iRand(0, x.size() - 1);
//    int b;
//
//    do{
//        b = (int) iRand(0, x.size() - 1);
//    }while(b == a);
//
//    iter_swap(x.begin() + a, x.begin() + b);
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
