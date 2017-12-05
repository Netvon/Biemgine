#pragma once
#include "dlldef.h"

#include <string>
#include <functional>

namespace biemgine {
    class BIEMGINE Thread
    {
    public:

        struct wrapper {
            virtual ~wrapper() {};
        };

        typedef int(*function)(void*);

        Thread(std::string name, function function);

    private:
        std::string threadName;
        wrapper thread;
    };
}
