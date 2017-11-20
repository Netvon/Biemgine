#include "Biemgine.h"
#include "NameGenerator.h"

namespace spacebiem
{

    NameGenerator::NameGenerator()
    {

        FileHandler fh("data/planet_names.csv");

        for each (vector<string> v in fh.getValues())
        {
            names.push_back(v[0]);
        }
    }

    string NameGenerator::getName() {
        return names[RandomGenerator::getInstance().generate(0, names.size() - 1)];
    }
}


