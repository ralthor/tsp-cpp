#ifndef FUNCTIONMINIMIZER_H
#define FUNCTIONMINIMIZER_H

#include "solution.h"

class FunctionMinimizer: public Solution<double>
{
    public:
        FunctionMinimizer();
        //~FunctionMinimizer();
        virtual double fitness();
        virtual void setValue(Solution<double> *);
        virtual void mutate(double); // probability is given as the parameter
        virtual void crossover(Solution<double> *);
        virtual int isBetterThan(Solution<double> *);
        virtual void randomize();
        virtual double getValue();
    private:
        double value;
};

#endif // FUNCTIONMINIMIZER_H
