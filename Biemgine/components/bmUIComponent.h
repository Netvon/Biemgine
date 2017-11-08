#pragma once

#include "dlldef.h"
#include "bmComponent.h"

namespace biemgine
{
    class BIEMGINE bmUIComponent :
        public bmComponent
    {
    public:

        bmUIComponent();
        ~bmUIComponent();

        template <typename TComponent>
        TComponent getComponentReference() const;

        void setComponentReference(bmComponent* component);

    private:
        bmComponent* componentReference = nullptr;
    };

    template<typename TComponent>
    TComponent bmUIComponent::getComponentReference() const
    {
        return dynamic_cast<TComponent>(componentReference);
    }
}
