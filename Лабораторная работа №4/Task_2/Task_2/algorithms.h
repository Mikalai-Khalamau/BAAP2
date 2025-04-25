#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include <vector>
class Algorithms
{
public:
    Algorithms();
    int BinPow (int digit, int powder, int mod);
    int InterpolationSearch(std::vector<int>&arr,int digit);
    int BinSearch(std::vector<int>&arr,int digit);
};

#endif // ALGORITHMS_H
