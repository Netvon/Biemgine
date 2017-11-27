#pragma once
#include "dlldef.h"
#include "TextureComponent.h"

#include <map>
#include <vector>

#include <initializer_list>

using std::string;
using std::map;
using std::vector;
using std::initializer_list;

namespace biemgine
{
    struct BIEMGINE TextureColumnDef {
        size_t count;
        int width;

        int padding = 0;
    };

    struct BIEMGINE TextureRowDef {
        size_t count;
        int height;

        int padding = 0;
    };

    class BIEMGINE AnimatedTextureComponent
        : public TextureComponent
    {
    public:
        AnimatedTextureComponent(
            string path,
            float offsetX,
            float offsetY,
            initializer_list<SizeRect> pRegions,
            initializer_list<size_t> pSequence,
            float pPlaybackSpeed = 1.f,
            int w = -1, int h = -1,
            unsigned int layer = 0,
            bool pVisible = true,
            const string pTag = "",
            Color color = Color::White(),
            float rotation = 0.0f,
            bool pPaused = false
        );

        AnimatedTextureComponent(
            string path,
            float offsetX,
            float offsetY,
            TextureColumnDef column,
            TextureRowDef row,
            float pPlaybackSpeed = 1.f,
            int w = -1, int h = -1,
            unsigned int layer = 0,
            bool pVisible = true,
            const string pTag = "",
            Color color = Color::White(),
            float rotation = 0.0f,
            bool pPaused = false
        );

        void doStep(float dt);

        bool isPausedOrStopped() const;
        void pause();
        void stop();
        void play();

        float getPlaybackSpeed() const;
        void setPlaybackSpeed(float pPlaybackSpeed);

        size_t getCurrentStep() const;
        SizeRect getCurrentRect() const;

    private:
        vector<SizeRect> regions;
        vector<size_t> sequence;
        size_t current = 0llu;

        float playbackSpeed = 1.f;
        float currentUpdate = playbackSpeed;

        bool paused = false;
    };
}
