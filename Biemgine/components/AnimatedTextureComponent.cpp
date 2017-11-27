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
        : TextureComponent(path, offsetX, offsetX, w, h, layer, pVisible, pTag, color, rotation),
        playbackSpeed(pPlaybackSpeed), paused(pPaused)
    {
        size_t count = 0llu;

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
                sequence.push_back(count);
                count++;
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
        currentUpdate = 60.0f;
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

    SizeRect AnimatedTextureComponent::getCurrentRect() const
    {
        return regions.at(current);
    }
}
