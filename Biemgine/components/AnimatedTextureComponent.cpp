#include "stdafx.h"
#include "AnimatedTextureComponent.h"

namespace biemgine
{
    AnimatedTextureComponent::AnimatedTextureComponent(
        string path,
        float offsetX, float offsetY,
        initializer_list<SizeRect> pRegions,
        initializer_list<size_t> pSequence,
        float pPlaybackSpeed,
        int w, int h,
        unsigned int layer,
        bool pVisible,
        const string pTag,
        Color color,
        float rotation,
        bool pPaused)
        : TextureComponent(path, offsetX, offsetX, w, h, layer, pVisible, pTag, color, rotation),
          regions(pRegions), sequence(pSequence), playbackSpeed(pPlaybackSpeed), paused(pPaused)
    {
        animations.insert(std::make_pair("default", AnimationSequenceDef{ pRegions, pSequence }));
    }

    AnimatedTextureComponent::AnimatedTextureComponent(
        string path,
        float offsetX, float offsetY,
        TextureColumnDef column, TextureRowDef row,
        float pPlaybackSpeed,
        int w, int h, unsigned int layer, bool pVisible, const string pTag, Color color, float rotation, bool pPaused)
        : AnimatedTextureComponent(path, offsetX, offsetX, column, row, initializer_list<size_t>(), pPlaybackSpeed, w, h, layer, pVisible, pTag, color, rotation)
    {
        size_t count = 0llu;

        for (size_t rowIndex = 0; rowIndex < row.count; rowIndex++)
        {
            for (size_t columnIndex = 0; columnIndex < column.count; columnIndex++)
            {
                sequence.push_back(count);
                count++;
            }
        }
    }

    AnimatedTextureComponent::AnimatedTextureComponent(
        string path,
        float offsetX, float offsetY,
        TextureColumnDef column, TextureRowDef row,
        initializer_list<size_t> pSequence,
        float pPlaybackSpeed,
        int w, int h, unsigned int layer, bool pVisible, const string pTag, Color color, float rotation, bool pPaused)
        : TextureComponent(path, offsetX, offsetX, w, h, layer, pVisible, pTag, color, rotation),
        playbackSpeed(pPlaybackSpeed), paused(pPaused), sequence(pSequence)
    {
        AnimationSequenceDef ani;

        for (size_t rowIndex = 0; rowIndex < row.count; rowIndex++)
        {
            for (size_t columnIndex = 0; columnIndex < column.count; columnIndex++)
            {
                Size s{ column.width, row.height };
                Point p{
                    static_cast<int>(column.width * columnIndex),
                    static_cast<int>(row.height * rowIndex)
                };

                if (rowIndex > 0llu) {
                    p.x += row.padding;
                }

                if (columnIndex > 0llu) {
                    p.y += column.padding;
                }

                SizeRect sr;
                sr.point = p;
                sr.size = s;

                ani.regions.push_back(sr);
            }
        }

        animations.insert(std::make_pair("default", ani));
        current_name = "default";
    }

    AnimatedTextureComponent::AnimatedTextureComponent(
        string path,
        float offsetX, float offsetY,
        initializer_list<AnimationDef> pSequence,
        float pPlaybackSpeed,
        int w, int h,
        unsigned int layer,
        bool pVisible, const string pTag, Color color, float rotation, bool pPaused)
        : TextureComponent(path, offsetX, offsetX, w, h, layer, pVisible, pTag, color, rotation), playbackSpeed(pPlaybackSpeed), paused(pPaused)
    {
        for (auto& def : pSequence) {

            if (current_name.empty()) {
                current_name = def.name;
            }

            AnimationSequenceDef ani;
            ani.loop = def.loop;

            size_t count = 0llu;

            for (size_t rowIndex = 0; rowIndex < def.rows.count; rowIndex++)
            {
                for (size_t columnIndex = 0; columnIndex < def.cols.count; columnIndex++)
                {
                    Size s{ def.cols.width, def.rows.height };
                    Point p{
                        static_cast<int>(def.cols.width * columnIndex),
                        static_cast<int>(def.rows.height * rowIndex)
                    };

                    if (rowIndex > 0llu) {
                        p.x += def.rows.padding;
                    }

                    if (columnIndex > 0llu) {
                        p.y += def.cols.padding;
                    }

                    SizeRect sr;
                    sr.point = p;
                    sr.size = s;

                    ani.regions.push_back(sr);
                    ani.sequence.push_back(count);
                    count++;
                }
            }

            animations.insert(std::make_pair(def.name, ani));
        }
    }

    void AnimatedTextureComponent::doStep(float dt)
    {
        if (paused)
            return;

        currentUpdate += dt;

        if (currentUpdate >= playbackSpeed) {
            current++;
            current %= sequence.size();

            currentUpdate = 0.f;
        }
    }

    bool AnimatedTextureComponent::isPausedOrStopped() const
    {
        return paused;
    }

    void AnimatedTextureComponent::pause()
    {
        paused = true;
    }

    void AnimatedTextureComponent::stop()
    {
        paused = true;
        currentUpdate = 0.0f;
        current = 0llu;
    }

    void AnimatedTextureComponent::play()
    {
        paused = false;
        currentUpdate = playbackSpeed;
    }

    float AnimatedTextureComponent::getPlaybackSpeed() const
    {
        return playbackSpeed;
    }

    void AnimatedTextureComponent::setPlaybackSpeed(float pPlaybackSpeed)
    {
        playbackSpeed = pPlaybackSpeed;
    }

    size_t AnimatedTextureComponent::getCurrentStep() const
    {
        return current;
    }

    const SizeRect& AnimatedTextureComponent::getCurrentRect() const
    {
        auto &s = sequence.at(current);
        return regions.at(s);
    }

    const SizeRect & AnimatedTextureComponent::getRect() const
    {
        auto &s = sequence.at(current);
        return regions.at(s);
    }

    void AnimatedTextureComponent::update(float dt)
    {
        if (paused)
            return;

        currentUpdate += dt;

        if (currentUpdate >= playbackSpeed) {
            current++;
            current %= sequence.size();

            currentUpdate = 0.f;
        }
    }

    const string & AnimatedTextureComponent::getCurrentName() const
    {
        // TODO: insert return statement here
    }

    void AnimatedTextureComponent::setCurrentName(string current)
    {
    }
}
