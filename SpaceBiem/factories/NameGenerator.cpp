#include "Biemgine.h"
#include "NameGenerator.h"

namespace spacebiem
{

    NameGenerator::NameGenerator()
    {

        FileHandler fh("planet_names.csv");

        for each (vector<string> v in fh.getValues())
        {
            names.push_back(v[0]);
        }
    }

    string NameGenerator::getName() {
        return names[RandomGenerator::getInstance().generate(0, static_cast<float>(names.size()) - 1)];
    }
}


