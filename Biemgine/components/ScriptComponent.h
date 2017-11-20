#pragma once

#include "dlldef.h"
#include "Component.h"
#include <String>
#include "ColorComponent.h"
#include "..\primitives\Primitives.h"
#include "..\entities\Entity.h"

#include <functional>

using std::function;

namespace biemgine
{
    class BIEMGINE ScriptComponent :
        public Component
    {
    public:
        ScriptComponent(function<void()> pScript);

        void run();

    private:
        function<void()> script;
    };
}