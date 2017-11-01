#include <iostream>
#include "environment.h"
#include "tspga.h"

#define p push_back

using namespace std;

int main()
{
    MyGraph g("48.txt");
//    Graph g("280.txt");
    cout << g.size() << endl;
    TSPGA solver(36, 18000, g, 3);
    vector<int> answer;
    answer = solver.solve();
    double fitness = solver.fitness(answer, 1);
    cout << fitness << endl;
    showVector(answer);
    return 0;
}
