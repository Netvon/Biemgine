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

        bool getIsMouseDown() const;
        bool getIsMouseOver() const;

    private:
        Component* componentReference = nullptr;

        bool isMouseDown = false;
        bool isMouseOver = false;
    };

    template<typename TComponent>
    TComponent UIComponent::getComponentReference() const
    {
        return dynamic_cast<TComponent>(componentReference);
    }
}
