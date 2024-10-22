#pragma once
#include "dlldef.h"
#include "TextureComponent.h"

#include <map>
#include <vector>
#include <functional>

#include <initializer_list>

using std::string;
using std::map;
using std::vector;
using std::initializer_list;

namespace biemgine
{
    struct BIEMGINE AnimationSequenceDef {
        vector<SizeRect> regions;
        vector<size_t> sequence;
        bool loop = true;
    };

    struct BIEMGINE TextureColumnDef {
        size_t count;
        int width;
        int offset = 0;

        int padding = 0;
    };

    struct BIEMGINE TextureRowDef {
        size_t count;
        int height;
        int offset = 0;

        int padding = 0;
    };

    struct BIEMGINE AnimationIndex {
        size_t row;
        size_t column;
    };

    struct BIEMGINE AnimationDef {
        string name;
        TextureColumnDef cols;
        TextureRowDef rows;
        bool loop = true;
    };

    struct BIEMGINE AnimationSequence {
        vector<AnimationIndex> sequence;
    };

    class BIEMGINE AnimatedTextureComponent
        : public TextureComponent
    {
    public:
        AnimatedTextureComponent(
            string path,
            float offsetX,
            float offsetY,
            TextureColumnDef column,
            TextureRowDef row,
            initializer_list<size_t> pSequence,
            float pPlaybackSpeed = 1.f,
            int w = -1, int h = -1,
            unsigned int layer = 0,
            bool pVisible = true,
            const string pTag = "",
            Color color = Color::White(),
            float rotation = 0.0f,
            bool pPaused = false,
            BLEND_MODE blend = BLEND_MODE::ALPHA_BLEND
        );

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
            bool pPaused = false,
            BLEND_MODE blend = BLEND_MODE::ALPHA_BLEND
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
            bool pPaused = false,
            BLEND_MODE blend = BLEND_MODE::ALPHA_BLEND
        );

        AnimatedTextureComponent(
            string path,
            float offsetX,
            float offsetY,
            initializer_list<AnimationDef> pSequence,
            string initialAnimation,
            float pPlaybackSpeed = 1.f,
            int w = -1, int h = -1,
            unsigned int layer = 0,
            bool pVisible = true,
            const string pTag = "",
            Color color = Color::White(),
            float rotation = 0.0f,
            bool pPaused = false,
            BLEND_MODE blend = BLEND_MODE::ALPHA_BLEND
        );

        //void doStep(float dt);

        bool isPausedOrStopped() const;
        void pause();
        void stop();
        void play();

        float getPlaybackSpeed() const;
        void setPlaybackSpeed(float pPlaybackSpeed);

        size_t getCurrentStep() const;
        //const SizeRect& getCurrentRect() const;
        const SizeRect& getRect() const override;
        void update(float dt) override;

        const string& getCurrentAnimation() const;
        void setCurrentAnimation(string key);

    private:

        std::function<void(string, bool)> onAnimationCycleComplete;

        vector<SizeRect> regions;
        vector<size_t> sequence;
        size_t current = 0llu;

        float playbackSpeed = 1.f;
        float currentUpdate = playbackSpeed;

        bool paused = false;

        map<string, AnimationSequenceDef> animations;
        string currentName;
        AnimationSequenceDef* currentAnimation = nullptr;
    };
}
