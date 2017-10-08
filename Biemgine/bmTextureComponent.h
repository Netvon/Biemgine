#pragma once
#include "bmComponent.h"
class bmTextureComponent :
	public bmComponent
{
public:
	bmTextureComponent(std::string path) : path(path) { };

	std::string& getPath() { return path; };

private:
	std::string path;
};

