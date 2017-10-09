#pragma once
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"

class bmSpriteEntity : public bmEntity
{
public:
	bmSpriteEntity(std::string texture, int x, int y, bmColor color, int w, int h) {

		addComponent("position", new bmPositionComponent(x, y));
		addComponent("texture", new bmTextureComponent(texture, w, h));
		addComponent("color", new bmColorComponent(color.r, color.g, color.b));
	}
};

