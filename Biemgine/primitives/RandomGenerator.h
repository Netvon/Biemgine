#pragma once

#include "dlldef.h"

#include <ctime>
#include <random>

namespace biemgine
{

    class BIEMGINE RandomGenerator
    {
    private:

        RandomGenerator(int seed)
        {
            generator.seed(seed);
        };

        std::default_random_engine generator;


    public:

        static RandomGenerator& getInstance()
        {
            static RandomGenerator instance((unsigned int)time(NULL));
            return instance;
        }
        RandomGenerator(RandomGenerator const&) = delete;
        void operator=(RandomGenerator const&) = delete;

        int generate(int min, int max);

    private:


    };
}
