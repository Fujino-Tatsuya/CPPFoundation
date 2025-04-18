#include "RandomGen.h"
#include <random>

int RandomGen::GetRandom(int min, int max)
{
    std::random_device rd;
    unsigned long long seed = rd();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<int> dist(min, max);

    return dist(gen);
}