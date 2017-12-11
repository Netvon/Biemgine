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

                regions.push_back(sr);
            }
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
}
