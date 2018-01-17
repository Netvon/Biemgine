#pragma once
#include "System.h"
#include "../entities/Entity.h"
#include "..\components\CameraComponent.h"
#include "..\components\PositionComponent.h"
#include "../components/TextComponent.h"
#include "..\components\TextureComponent.h"
#include "..\components\AnimatedTextureComponent.h"
#include "../devices/graphics/GraphicsDevice.h"
#include "../devices/graphics/TextureFlip.h"

#include <list>
#include <memory>
#include <algorithm>

using std::string;
using std::list;

namespace biemgine
{
    struct OptDrawable
    {
        Entity* entity;
        std::shared_ptr<PositionComponent> positionComponent;
        bool isUI;
        int type;
        int layer;
    };

    struct OptDrawTexture : public OptDrawable
    {
        std::shared_ptr<TextureComponent> textureComponent; 
    };

    struct OptDrawText  : public OptDrawable
    {
        std::shared_ptr<TextComponent> textComponent;
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
        vector<std::shared_ptr<OptDrawable>> optDrawableList;
        std::shared_ptr<CameraComponent> cameraComponent = nullptr;
        
    };
}
