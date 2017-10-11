#include "stdafx.h"
#include "bmColorComponent.h"


bmColorComponent::bmColorComponent(int r, int g, int b, int a)
{
	color = { r, g, b, a };
}

bmColorComponent::bmColorComponent(bmColor bmColor)
{
	color = bmColor;
}
