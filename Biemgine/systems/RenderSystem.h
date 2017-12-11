#pragma once
#include "System.h"
#include "../entities/Entity.h"
#include "../components/CameraComponent.h"
#include "..\components\PositionComponent.h"
#include "../components/TextComponent.h"
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
        std::shared_ptr<TextureComponent> textureComponent;
        std::shared_ptr<PositionComponent> positionComponent;
        bool isUI;
    };

    struct OptDrawText
    {
        std::shared_ptr<TextComponent> textComponent;
        std::shared_ptr<PositionComponent> positionComponent;
        bool isUI;
    };

    struct DrawTexture
    {
        string path;
        int x, y, w, h;
        Color color;
        float angle;
        unsigned int layer;
        bool center;
        TextureFlip flip;
        SizeRect rect;

        DrawTexture(const string& path, int x, int y, int w, int h, float angle, Color color, unsigned int layer, bool center, TextureFlip flip, SizeRect rect = SizeRect::empty());
    };

    struct DrawText
    {
        Font font;
        string text;
        int x, y;
        Color color;
        std::shared_ptr<TextComponent> component;
        bool center;

        DrawText(Font font, const string& text, int x, int y, Color color, std::shared_ptr<TextComponent> component, bool center);
    };

    class RenderSystem
        : public System
    {
    public:
        ~RenderSystem();;

        void setGraphicsDevice(GraphicsDevice* graphicsDevice);

        void update(const Entity& entity, const float deltaTime) override;
        void onSceneSwitch() override;
        //void before(const float deltaTime) override;
        void after(const float deltaTime) override;

    private:
        GraphicsDevice* graphicsDevice = nullptr;
        list<OptDrawTexture> optDrawList;
        list<OptDrawText> optTextList;
        list<DrawTexture> drawList;
        list<DrawText> textList;
        std::shared_ptr<CameraComponent> cameraComponent = nullptr;
        
    };
}
