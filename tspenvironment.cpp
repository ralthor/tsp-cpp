#include "tspenvironment.h"

#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

//double fRand(double fmin, double fmax)
//{
//    double f = (double) rand() / RAND_MAX;
//    return fmin + f * (fmax - fmin);
//}

TSPEnvironment::TSPEnvironment(Graph g)
{
    graph = g;
//    x = vector<double>(n, 0);
//    velocity = vector<double>(n, 0);
//    pbest = vector<double>(n, 0);
}

TSPEnvironment::~TSPEnvironment()
{
    //dtor
}

//void TSPEnvironment::randomize()
//{
//    srand(time(NULL));
//    double fgbest = -10;
//    gbest = -1;
//    for(unsigned int i = 0; i < x.size(); i++)
//    {
//        x[i] = fRand(-5, 5);
//        pbest[i] = x[i];
//        velocity[i] = fRand(-0.3, 0.3);
//
//        double tmp = fitness(x[i]);
//        if(tmp > fgbest)
//        {
//            fgbest = tmp;
//            gbest = x[i];
//        }
//    }
//}
//
//double TSPEnvironment::fitness(double x)
//{
//    if(x > 5 || x < -5)
//        return 0;
//    return sin(10 * x) + sin(11 * x);
//}
//
//double TSPEnvironment::solve(double e)
//{
//    double old_gbest;
//    int i = 0;
//    randomize();
//    do {
//        old_gbest = gbest;
//        calculateNewVelocities();
//        updateValues();
//    } while(fabs(gbest - old_gbest) > e || i++ < 10000);
//    cout << "iterations: " << i << endl;
//    return gbest;
//}
//void TSPEnvironment::calculateNewVelocities()
//{
//    double inertia = 0.7;
//    double c1, c2, r1, r2;
//    c1 = c2 = 2;
//    r1 = fRand(0, 1);
//    r2 = fRand(0, 1);
//    for(unsigned int i = 0; i < x.size(); i++)
//        velocity[i] = inertia * velocity[i] + c1 * r1 * (gbest - x[i]) + c2 * r2 * (pbest[i] - x[i]);
//}
//
//void TSPEnvironment::updateValues()
//{
//    double fgbest = fitness(gbest);
//    for(unsigned int i = 0; i < x.size(); i++)
//    {
//        x[i] += velocity[i];
//        double fx = fitness(x[i]);
//        if(fx > pbest[i])
//        {
//            pbest[i] = fx;
//            if(fx > fgbest)
//            {
//                gbest = x[i];
//                fgbest = fx;
//            }
//        }
//    }
//}
