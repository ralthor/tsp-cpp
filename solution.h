#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>

template <class T>
class Solution
{
    public:
        virtual double fitness();
        virtual void setValue(Solution *);
        virtual void mutate(double); // probability is given as the parameter
        virtual void crossover(Solution *);
        virtual int isBetterThan(Solution *);
        virtual void randomize();
        virtual T getValue();
    protected:
        T value;
};

#endif // SOLUTION_H
