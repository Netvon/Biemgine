#pragma once

#include "dlldef.h"
#include <string>
#include "Component.h"

using std::string;

namespace biemgine
{
    class BIEMGINE TextureComponent :
        public Component
    {
    public:
        TextureComponent(string path, float offsetX, float offsetY, int w = -1, int h = -1, unsigned int layer = 0, bool pVisible = true, const string pTag = "");
        ~TextureComponent();

        const string& getPath();
        int getWidth() const;
        int getHeight() const;
        float getOffsetX() const;
        float getOffsetY() const;
        unsigned int getLayer() const;

        const string & getTag() const;
        bool isVisible() const;
        void setVisible(bool pVisible);

    private:
        string path;
        int width, height;
        float offsetX, offsetY;
        unsigned int layer;
        const string tag;
        bool visible;
    };
}
