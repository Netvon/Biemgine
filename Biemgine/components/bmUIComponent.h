#pragma once

#include "bmComponent.h"

namespace biemgine
{
    class bmUIComponent :
        public bmComponent
    {
    public:
        template <typename TComponent>
        TComponent getComponentReference() const {
            return dynamic_cast<TComponent>(componentReference);
        }

        void setComponentReference(bmComponent* component)
        {
            componentReference = component;
        }

    private:
        bmComponent* componentReference = nullptr;
    };
}
