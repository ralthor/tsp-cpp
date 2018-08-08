#include <cstdlib>
#include "function_minimizer.h"

double FunctionMinimizer::fitness()
{
    return value * value + 10;
}

void FunctionMinimizer::setValue(Solution<double> *s) {
    value = s->getValue();
}

void FunctionMinimizer::mutate(double) {
    value += (double) std::rand() / RAND_MAX - 0.5;
}


void FunctionMinimizer::crossover(Solution<double> *s) {
    double p = (double) std::rand() / RAND_MAX;
    value = value * p + s->getValue() * (1 - p);
}


int FunctionMinimizer::isBetterThan(Solution<double> *s) {
    return fitness() < s->fitness();
}


void FunctionMinimizer::randomize() {
    value = (double) std::rand() / RAND_MAX * 10;
}

double FunctionMinimizer::getValue() {
    return value;
}
