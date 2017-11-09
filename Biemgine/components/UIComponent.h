#pragma once

#include "dlldef.h"
#include "Component.h"

namespace biemgine
{
    class BIEMGINE UIComponent :
        public Component
    {
    public:

        UIComponent();
        ~UIComponent();

        template <typename TComponent>
        TComponent getComponentReference() const;

        void setComponentReference(Component* component);

    private:
        Component* componentReference = nullptr;
    };

    template<typename TComponent>
    TComponent UIComponent::getComponentReference() const
    {
        return dynamic_cast<TComponent>(componentReference);
    }
}
