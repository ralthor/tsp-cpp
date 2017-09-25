#ifndef SOLUTION_H
#define SOLUTION_H

#include <string>

template <class T>
class Solution
{
    public:
        Solution();
        Solution(T);
        //~Solution();
        double fitness();
        std::string serialize();
        void set(T);
        T get();

    private:
        T value;
};

#endif // SOLUTION_H
