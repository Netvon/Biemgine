#include "SaveBlobEntityComponentBuilder.h"

namespace spacebiem
{
    SaveBlobEntityComponentBuilder::SaveBlobEntityComponentBuilder()
    {}

    void SaveBlobEntityComponentBuilder::prepare(string pComponentName)
    {
        values.clear();

        componentName = pComponentName;
    }

    void SaveBlobEntityComponentBuilder::addValue(string value)
    {
        values.push_back(value);
    }

    string SaveBlobEntityComponentBuilder::build()
    {
        string blob = componentName + ",";

        for (auto it = values.begin(); it != values.end(); ++it) {
            if (it != values.begin())
                blob += ",";

            blob += (*it);
        }

        return blob;
    }
}
