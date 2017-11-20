#include "Biemgine.h"
#include "CameraComponent.h"

namespace spacebiem
{
    CameraComponent::CameraComponent() : deltaX(0.0f), deltaY(0.0f) {}

    float CameraComponent::getDeltaX() const { return deltaX; }
    float CameraComponent::getDeltaY() const { return deltaY; }
    int CameraComponent::getWindowWidth() const { return windowWidth; }
    int CameraComponent::getWindowHeight() const { return windowHeight; }
    void CameraComponent::setDeltaX(float x) { deltaX = x; }
    void CameraComponent::setDeltaY(float y) { deltaY = y; }
    void CameraComponent::setWindowWidth(int width) { windowWidth = width; }
    void CameraComponent::setWindowHeight(int height) { windowHeight = height; }
}
