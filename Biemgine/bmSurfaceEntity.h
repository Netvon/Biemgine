#pragma once
#include "bmEntity.h"
#include "bmPositionComponent.h"
#include "bmColorComponent.h"
#include "bmTextureComponent.h"
#include "bmPhysicsComponent.h"
#include "bmRectangleComponent.h"

class bmSurfaceEntity : public bmEntity
{
public:
	bmSurfaceEntity(int x, int y, int r, int g, int b, int w, int h) {
		addComponent("position", new bmPositionComponent(x, y));
		addComponent("rectangle", new bmRectangleComponent(w, h, { r,g,b,255 }));
		addComponent("physics", new bmPhysicsComponent(static_cast<float>(w), static_cast<float>(h), true, RECTANGLE));
	}
};

