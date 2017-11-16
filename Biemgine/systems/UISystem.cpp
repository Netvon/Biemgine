#include "UISystem.h"
#include "..\components\UIComponent.h"
#include "..\components\PositionComponent.h"

namespace biemgine
{
    UISystem::~UISystem()
    {
    }

    void UISystem::before()
    {
        auto im = getStateManager()->getInputManager();

        currentMouseLocation = im->getMouseLocation();
        isLeftMouseDown = im->isLeftMouseDown();
    }

    void UISystem::update(const Entity & entity)
    {
        if (!entity.hasComponent("ui") || !entity.hasComponent("position"))
            return;

        auto ui = entity.getComponent<UIComponent*>("ui");
        auto position = entity.getComponent<PositionComponent*>("position");

        auto size = ui->getSize();

        auto X1 = position->getX();
        auto X2 = X1 + size.width;

        auto Y1 = position->getY();
        auto Y2 = Y1 + size.height;

        if (currentMouseLocation.x >= X1
            && currentMouseLocation.x <= X2
            && currentMouseLocation.y >= Y1
            && currentMouseLocation.y <= Y2) {

            ui->setIsMouseOver(true);
            ui->setIsMouseDown(isLeftMouseDown);

            if (isLeftMouseDown) {
                ui->getIsClicked()(const_cast<StateManager*>(transitionManager));
            }
        }
        else {
            ui->setIsMouseOver(false);
            ui->setIsMouseDown(false);
        }
    }

    inline void UISystem::before(const float deltaTime) {}
    inline void UISystem::update(const Entity & entity, const float deltaTime) {}
    inline void UISystem::after() {}
    inline void UISystem::after(const float deltaTime) {}
    inline void UISystem::onSceneSwitch() {}
}
