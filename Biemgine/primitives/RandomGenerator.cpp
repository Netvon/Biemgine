
#include "stdafx.h"
#include "RandomGenerator.h"
#include <functional>


namespace biemgine
{
    RandomGenerator::RandomGenerator(int seed)
    {
        generator.seed(seed);
    }

    RandomGenerator & RandomGenerator::getInstance()
    {
        static RandomGenerator instance((unsigned int)time(NULL));
        return instance;
    }

    float RandomGenerator::generate(float min, float max)
    {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dis(min, max);

        return dis(gen);
    }
}
