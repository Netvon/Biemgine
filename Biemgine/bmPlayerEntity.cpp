#include "stdafx.h"
#include "bmPlayerEntity.h"



bmPlayerEntity::bmPlayerEntity() : bmEntity()
{

	// Add in each specific entity the right components.
	componentHashmap["position"] = new bmPositionComponent(50,50);
	// Renderable component...
	// Movable component...
	// Collision component...



}
