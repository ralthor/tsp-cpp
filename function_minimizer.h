#ifndef FUNCTIONMINIMIZER_H
#define FUNCTIONMINIMIZER_H

#include "solution.h"

class FunctionMinimizer: public Solution<double>
{
    public:
        FunctionMinimizer();
        //~FunctionMinimizer();
        double fitness();
    private:
};

#endif // FUNCTIONMINIMIZER_H
