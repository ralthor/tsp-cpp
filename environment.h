#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>

using namespace std;

class Environment
{
    public:
        Environment(int n);
        ~Environment();
        void randomize();
        double fitness(double x);
        double solve(double e);
    private:
        vector<double> x;
        vector<double> velocity;
        vector<double> pbest;
        double gbest;
        void calculateNewVelocities();
        void updateValues();
};

#endif // ENVIRONMENT_H
