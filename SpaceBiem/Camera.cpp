#include "Biemgine.h"
#include "Camera.h"

namespace spacebiem
{
    Camera::Camera() : deltaX(0.0f), deltaY(0.0f) {}

    float Camera::getDeltaX() const { return deltaX; }
    float Camera::getDeltaY() const { return deltaY; }
    int Camera::getWindowWidth() const { return windowWidth; }
    int Camera::getWindowHeight() const { return windowHeight; }
    void Camera::setDeltaX(float x) { deltaX = x; }
    void Camera::setDeltaY(float y) { deltaY = y; }
    void Camera::setWindowWidth(int width) { windowWidth = width; }
    void Camera::setWindowHeight(int height) { windowHeight = height; }
}
