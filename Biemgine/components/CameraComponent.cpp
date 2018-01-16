#include "CameraComponent.h"

namespace biemgine
{
    CameraComponent::CameraComponent(std::string onlyWithSuffix) : onlyWithSuffix(onlyWithSuffix), deltaX(0.0f), deltaY(0.0f) {}

    float CameraComponent::getDeltaX() const { return deltaX; }
    float CameraComponent::getDeltaY() const { return deltaY; }
    int CameraComponent::getWindowWidth() const { return windowWidth; }
    int CameraComponent::getWindowHeight() const { return windowHeight; }
    float CameraComponent::getOriginX() const
    {
        return originX;
    }
    float CameraComponent::getOriginY() const
    {
        return originY;
    }

    std::string CameraComponent::getOnlyWithSuffix() const
    {
        return onlyWithSuffix;
    }


    void CameraComponent::setDeltaX(float x) { deltaX = x; }
    void CameraComponent::setDeltaY(float y) { deltaY = y; }
    void CameraComponent::setWindowWidth(int width) { windowWidth = width; }
    void CameraComponent::setWindowHeight(int height) { windowHeight = height; }
    void CameraComponent::setOriginX(float x)
    {
        originX = x;
    }
    void CameraComponent::setOriginY(float y)
    {
        originY = y;
    }
}
