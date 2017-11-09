#pragma once
#include "System.h"
#include "../entities/Entity.h"
#include "../components/TextComponent.h"
#include "../devices/graphics/GraphicsDevice.h"

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

        DrawTexture(const string& path, int x, int y, int w, int h, float angle, Color color, unsigned int layer);
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
    };
}
