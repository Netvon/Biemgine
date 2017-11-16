#pragma once

#include "dlldef.h"
#include <functional>
#include "Component.h"
#include "..\managers\StateManager.h"
#include "..\primitives\Primitives.h"
#include "..\systems\UISystem.h"

using std::function;

namespace biemgine
{
    class BIEMGINE UIComponent :
        public Component
    {
    public:

        UIComponent();
        UIComponent(const Size& pSize, function<void (StateManager*)> onClick = nullptr);
        ~UIComponent();

        template <typename TComponent>
        TComponent getComponentReference() const;

        void setComponentReference(Component* component);

        bool getIsMouseDown() const;
        bool getIsMouseOver() const;

        const Size& getSize() const;

        function<void(StateManager*)> getIsClicked() const;

    protected:
        void setIsMouseOver(bool pIsMouseOver);
        void setIsMouseDown(bool pIsMouseDown);

        friend void UISystem::update(const Entity & entity);

    private:
        Component* componentReference = nullptr;

        bool isMouseDown = false;
        bool isMouseOver = false;
        Size size;
        function<void(StateManager*)> onClick;
    };

    template<typename TComponent>
    TComponent UIComponent::getComponentReference() const
    {
        return dynamic_cast<TComponent>(componentReference);
    }
}
