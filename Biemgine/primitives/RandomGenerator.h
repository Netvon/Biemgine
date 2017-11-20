#pragma once

#include "dlldef.h"

#include <ctime>
#include <random>

namespace biemgine
{

    class BIEMGINE RandomGenerator
    {
    private:

        RandomGenerator(int seed);
        std::default_random_engine generator;
    public:
        static RandomGenerator& getInstance();

        RandomGenerator(RandomGenerator const&) = delete;
        void operator=(RandomGenerator const&) = delete;

        template<typename T = int>
        T generate(T min, T max);

        float generate(float min, float max);
    };

    template<typename T>
    T RandomGenerator::generate(T min, T max)
    {
        std::uniform_int_distribution<T> distribution(min, max);
        return distribution(generator);
    }
}
