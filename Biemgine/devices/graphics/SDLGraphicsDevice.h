#pragma once

#include "GraphicsDevice.h"
#include <SDL_ttf.h>
#include "TextureAndUsage.h"
#include <map>

using std::string;

namespace biemgine
{
    class SDLGraphicsDevice :
        public GraphicsDevice
    {
    public:
        SDLGraphicsDevice(SDL_Window* window);
        ~SDLGraphicsDevice();

        void drawSquare(int x, int y, int w, int h, Color color, float angle = 0) const override;
        void drawTexture(const string& path, int x, int y, int w = -1, int h = -1, float angle = 0, Color color = { 255, 255, 255 }, TextureFlip flip = NONE, bool useCenterAsOrigin = false, SizeRect source = SizeRect::empty(), TextureComponent::BLEND_MODE blend = TextureComponent::BLEND_MODE::ALPHA_BLEND) override;
        Size drawText(const Font& font, const string& text, int x, int y, Color color, int ptSize, TextureFlip flip = NONE, bool center = false) override;
        void clear() const override;
        void present() override;

    private:
        SDL_Renderer* renderer = nullptr;

        std::map<Font, TTF_Font*> fonts;

        std::map<std::string, SDL_Texture*> textures;
        std::map<std::pair<Font,std::string>, TextureAndUsage> textTextures;

        SDL_Texture* getTexture(std::string path);
    };
}
