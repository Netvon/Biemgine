#pragma once

#include "Biemgine.h"
#include "..\components\GravityComponent.h"

using biemgine::System;
using biemgine::Entity;
using biemgine::Vector;

using biemgine::PositionComponent;
using biemgine::PhysicsComponent;
using biemgine::AffectedByGravityComponent;
using biemgine::PhysicsComponent;
using biemgine::AnimatedTextureComponent;
using biemgine::TextureFlip;
using biemgine::CollidableComponent;

namespace spacebiem
{
	class MovementSystem :
		public System
	{
	public:
		struct MoveEntry
		{
			Entity* entity;
			std::shared_ptr<PositionComponent> positionComponent;
			std::shared_ptr<AnimatedTextureComponent> animatedTextureComponent;
			std::shared_ptr<PhysicsComponent> physicsComponent;
			std::shared_ptr<AffectedByGravityComponent> affectedByGravityComponent;
			std::shared_ptr<CollidableComponent> collidableComponent;
		};

		void onAddEntity(Entity& entity) override;
		void update() override;
		void setAnimationSpeed(const float &escapeVelocity, std::shared_ptr<biemgine::PhysicsComponent> &physics, std::shared_ptr<biemgine::AnimatedTextureComponent> &texture);

	private:
		vector<MoveEntry> moveEntries;
	};
}
