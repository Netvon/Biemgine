#pragma once
#include "System.h"
#include "../entities/Entity.h"
#include "..\components\CameraComponent.h"
#include "..\components\PositionComponent.h"
#include "../components/TextComponent.h"
#include "..\components\TextBoxComponent.h"
#include "..\components\TextureComponent.h"
#include "..\components\AnimatedTextureComponent.h"
#include "../devices/graphics/GraphicsDevice.h"
#include "../devices/graphics/TextureFlip.h"

#include <list>
#include <memory>

using std::string;
using std::list;

namespace biemgine
{
    struct OptDrawTexture
    {
        Entity* entity;
        std::shared_ptr<TextureComponent> textureComponent;
        std::shared_ptr<PositionComponent> positionComponent;
        bool isUI;
    };

    struct OptDrawText
    {
        Entity* entity;
        std::shared_ptr<TextComponent> textComponent;
        std::shared_ptr<PositionComponent> positionComponent;
        bool isUI;
    };

    class RenderSystem
        : public System
    {
    public:
        ~RenderSystem();;

        void setGraphicsDevice(GraphicsDevice* graphicsDevice);

        void onAddEntity(Entity & entity) override;
        void update(const float deltaTime) override;
        void onSceneSwitch() override;

    private:
        GraphicsDevice* graphicsDevice = nullptr;
        list<OptDrawTexture> optDrawList;
        list<OptDrawText> optTextList;
        std::shared_ptr<CameraComponent> cameraComponent = nullptr;
        
    };
}
