#pragma once
#include "System.h"
#include "../entities/Entity.h"
#include "../components/TextComponent.h"
#include "../devices/graphics/GraphicsDevice.h"
#include "../devices/graphics/TextureFlip.h"

#include <list>

using std::string;
using std::list;

namespace biemgine
{
    struct DrawTexture
    {
        string path;
        int x, y, w, h;
        Color color;
        float angle;
        unsigned int layer;
        bool center;
        TextureFlip flip;

        DrawTexture(const string& path, int x, int y, int w, int h, float angle, Color color, unsigned int layer, bool center, TextureFlip flip);
    };

    struct DrawText
    {
        Font font;
        string text;
        int x, y;
        Color color;
        TextComponent* component;
        bool center;

        DrawText(Font font, const string& text, int x, int y, Color color, TextComponent* component, bool center);
    };

    class RenderSystem
        : public System
    {
    public:
        ~RenderSystem();;

        void setGraphicsDevice(GraphicsDevice* graphicsDevice);

        void update(const Entity& entity, const float deltaTime) override;
        void onSceneSwitch() override;
        void before(const float deltaTime) override;
        void after(const float deltaTime) override;

    private:
        GraphicsDevice* graphicsDevice = nullptr;
        list<DrawTexture> drawList;
        list<DrawText> textList;
    };
}
