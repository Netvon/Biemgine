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

        UIComponent(bool pEnabled = true);
        UIComponent(const Size& pSize, function<void (StateManager*)> onClick = nullptr, function<void(StateManager*)> onEnter = nullptr, bool pEnabled = true);
        ~UIComponent();

        template <typename TComponent>
        std::shared_ptr<TComponent> getComponentReference() const;

        void setComponentReference(std::shared_ptr<Component> component);

        bool getIsMouseDown() const;
        bool getIsMouseOver() const;

        const Size& getSize() const;

        function<void(StateManager*)> getIsClicked() const;
        function<void(StateManager*)> getIsEntered() const;
        bool isEnabled() const;

    protected:
        void setIsMouseOver(bool pIsMouseOver);
        void setIsMouseDown(bool pIsMouseDown);

        friend void UISystem::update(const Entity & entity, const float deltaTime);

    private:
        std::shared_ptr<Component> componentReference = nullptr;

        bool isMouseDown = false;
        bool isMouseOver = false;
        Size size;
        function<void(StateManager*)> onClick;
        function<void(StateManager*)> onEnter;
        bool enabled;
    };

    template<typename TComponent>
    std::shared_ptr<TComponent> UIComponent::getComponentReference() const
    {
        return std::dynamic_pointer_cast<TComponent>(componentReference);
    }
}
