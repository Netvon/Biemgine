#pragma once
#include "bmSystem.h"
#include "bmEntity.h"
#include "GraphicsDevice.h"

#include <list>

using namespace std;

struct DrawTexture {
    string path;
    int x, y, w, h;
    bmColor color;
    float angle;
    unsigned int layer;

    DrawTexture(string path, int x, int y, int w, int h, float angle, bmColor color, unsigned int layer) :
        path(path), x(x), y(y), w(w), h(h), color(color), angle(angle), layer(layer) {};
};

class bmRenderSystem 
    : public bmSystem
{
public:

    ~bmRenderSystem()
    {
        cout << "Render System is being deleted" << endl;
    };

    void setGraphicsDevice(GraphicsDevice* graphicsDevice);

    void update(const bmEntity& entity, const float deltaTime) override;
    void onSceneSwitch() override;
    void before(const float deltaTime) override;
    void after(const float deltaTime) override;

private:
    GraphicsDevice* graphicsDevice = nullptr;
    list<DrawTexture> drawList;
};
