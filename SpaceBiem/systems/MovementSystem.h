#pragma once

#include "Biemgine.h"

using biemgine::System;
using biemgine::Entity;
using biemgine::PhysicsComponent;
using biemgine::Vector;

namespace spacebiem
{
	class MovementSystem :
		public System
	{
	public:
		void update(const Entity& entity) override;
		void setAnimationSpeed(const float &escapeVelocity, std::shared_ptr<biemgine::PhysicsComponent> &physics, std::shared_ptr<biemgine::AnimatedTextureComponent> &texture);
	};
}
