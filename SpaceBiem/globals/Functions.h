#pragma once

#include "Biemgine.h"
#include <functional>

using biemgine::Entity;

namespace spacebiem
{
    class Functions
    {
    public:
        static std::function<void(float)> updateAnimatedBasesOnSpeed(std::shared_ptr<biemgine::GroundedComponent> grounded, std::shared_ptr<biemgine::AnimatedTextureComponent> texture, std::shared_ptr<biemgine::PhysicsComponent> physics) {

            return [grounded, texture, physics](float deltatime) {
                constexpr char* animation = "walk";
                constexpr float escapeVelocity = 140.0f;

                if (grounded->isGrounded()) {

                    if (texture->getCurrentAnimation() != animation) {
                        texture->setCurrentAnimation(animation);
                    }

                    if (texture->isPausedOrStopped())
                        texture->play();

                    if (physics->getVelocity().length() > 1.0f) {

                        auto veloPercentage = escapeVelocity / physics->getVelocity().length();
                        auto maxSpeed = 32.0f;
                        texture->setPlaybackSpeed(maxSpeed * veloPercentage);
                    }
                    else
                    {
                        texture->stop();
                    }
                }
                else {

                    if (texture->getCurrentAnimation() == animation)
                        texture->stop();
                }
            };
        }

        static std::function<void(biemgine::StateManager*)> buttonHoverSound() {
            return [](biemgine::StateManager* e) {
                e->getAudioDevice().playSoundEffect("audio/switch.mp3", 0, -1, 128);
            };
        }

        static std::function<void(biemgine::StateManager*)> buttonClickSound() {
            return [](biemgine::StateManager* e) {
                e->getAudioDevice().playSoundEffect("audio/idroid.mp3", 0, -1, 128);
            };
        }

        template<typename P>
        static std::function<void(P)> combine(std::function<void(P)> a, std::function<void(P)> b);

        template<typename P>
        static std::function<void(P)> do_if(std::function<bool()> a, std::function<void(P)> b);
    };

    template<typename P>
    std::function<void(P)> Functions::combine(std::function<void(P)> a, std::function<void(P)> b)
    {
        return [a, b](P param) {
            if(a)
                a(param);

            if(b)
                b(param);
        };
    }

    template<typename P>
    std::function<void(P)> Functions::do_if(std::function<bool()> a, std::function<void(P)> b)
    {
        return [a, b](P param) {

            if (a()) {
                b(param);
            }
        };
    }
}
