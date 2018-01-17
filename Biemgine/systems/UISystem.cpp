#include "UISystem.h"

namespace biemgine
{
    UISystem::UISystem() : sceneWasSwitched(true) {}

    void UISystem::onAddEntity(Entity & entity)
    {
        auto ui = entity.getComponent<UIComponent>("ui");
        auto position = entity.getComponent<PositionComponent>("position");

        if (ui != nullptr && position != nullptr)
        {
            Entry entry;
            entry.entity = &entity;
            entry.positionComponent = position;
            entry.uiComponent = ui;

            entries.push_back(std::move(entry));
        } 
    }

    void UISystem::before(const float deltaTime)
    {
        auto im = getStateManager()->getInputManager();

        currentMouseLocation = im->getMouseLocation();

        isLeftMouseDown = im->isLeftMouseDown();

        if (sceneWasSwitched && clickCoolDown > 0.0f)
        {
            clickCoolDown -= (deltaTime / 1000.f);
        }
        else if (sceneWasSwitched && clickCoolDown <= 0.5f)
        {
            sceneWasSwitched = false;
            clickCoolDown = 0.5f;
        }
    }

    void UISystem::update(const float deltaTime)
    {
        if (sceneWasSwitched)
            return;

        for (const Entry& entry : entries)
        {
            if (!entry.entity->isAlive()) continue;

            auto sizeRect = entry.uiComponent->getSize();

            auto X1 = entry.positionComponent->getX() + sizeRect.point.x;
            auto X2 = X1 + sizeRect.size.width;

            auto Y1 = entry.positionComponent->getY() + sizeRect.point.y;
            auto Y2 = Y1 + sizeRect.size.height;

            if (currentMouseLocation.x >= X1
                && currentMouseLocation.x <= X2
                && currentMouseLocation.y >= Y1
                && currentMouseLocation.y <= Y2) {

                if (!entry.uiComponent->getIsMouseOver() && entry.uiComponent->getIsEntered())
                    entry.uiComponent->getIsEntered()(getStateManager());

                if (isLeftMouseDown && !entry.uiComponent->getIsMouseDown())
                {
                    if (entry.uiComponent->getIsClicked())
                        entry.uiComponent->getIsClicked()(getStateManager());
                }

                entry.uiComponent->setIsMouseOver(true);
                entry.uiComponent->setIsMouseDown(isLeftMouseDown);

                
            }
            else {
                entry.uiComponent->setIsMouseOver(false);
                entry.uiComponent->setIsMouseDown(false);
            }
        }
    }
}
