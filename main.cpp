#include <iostream>
#include "environment.h"
//#include "function_minimizer.h"
//#include "graph.h"
#include "tspga.h"

#define p push_back

using namespace std;

int main()
{
    Graph g("48.txt");
    cout << g.size() << endl;
    TSPGA solver(80, 15000, g);
    vector<int> answer = solver.solve();
    double fitness = solver.fitness(answer, 1);
    cout << fitness << endl;
    showVector(answer);
    return 0;
}
