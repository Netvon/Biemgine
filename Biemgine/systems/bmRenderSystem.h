#pragma once
#include "bmSystem.h"
#include "../entities/bmEntity.h"
#include "../components/bmTextComponent.h"
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
        bmColor color;
        float angle;
        unsigned int layer;

        DrawTexture(const string& path, int x, int y, int w, int h, float angle, bmColor color, unsigned int layer);
    };

    class bmRenderSystem
        : public bmSystem
    {
    public:
        ~bmRenderSystem();;

        void setGraphicsDevice(GraphicsDevice* graphicsDevice);

        void update(const bmEntity& entity, const float deltaTime) override;
        void onSceneSwitch() override;
        void before(const float deltaTime) override;
        void after(const float deltaTime) override;

    private:
        GraphicsDevice* graphicsDevice = nullptr;
        list<DrawTexture> drawList;
    };
}
