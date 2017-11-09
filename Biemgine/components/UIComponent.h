#pragma once

#include "dlldef.h"
#include "Component.h"
#include "..\primitives\Primitives.h"
#include "..\systems\UISystem.h"

namespace biemgine
{
    class BIEMGINE UIComponent :
        public Component
    {
    public:

        UIComponent();
        UIComponent(const Size& pSize);
        ~UIComponent();

        template <typename TComponent>
        TComponent getComponentReference() const;

        void setComponentReference(Component* component);

        bool getIsMouseDown() const;
        bool getIsMouseOver() const;

        const Size& getSize() const;

    protected:
        void setIsMouseOver(bool pIsMouseOver);
        void setIsMouseDown(bool pIsMouseDown);

        friend void UISystem::update(const Entity & entity);

    private:
        Component* componentReference = nullptr;

        bool isMouseDown = false;
        bool isMouseOver = false;
        Size size;
    };

    template<typename TComponent>
    TComponent UIComponent::getComponentReference() const
    {
        return dynamic_cast<TComponent>(componentReference);
    }
}
