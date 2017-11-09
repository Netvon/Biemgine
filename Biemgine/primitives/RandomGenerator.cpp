
#include "stdafx.h"
#include "RandomGenerator.h"


namespace biemgine
{

    int RandomGenerator::generate(int min, int max)
    {
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(generator);
    }
}
