#include "stdafx.h"
#include "bmTexture2d.h"

bmTexture2d::bmTexture2d()
	:	width(0), height(0),
		internalFormat(GL_RGB), imageFormat(GL_RGB),
		wrapS(GL_REPEAT), wrapT(GL_REPEAT),
		filterDownscale(GL_LINEAR), filterUpscale(GL_LINEAR)
{
	glGenTextures(1, &id);
}

void bmTexture2d::create(unsigned int width, unsigned int height, unsigned char * textureData)
{
	this->width = width;
	this->height = height;

	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE, textureData);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterDownscale);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterUpscale);

	glBindTexture(GL_TEXTURE_2D, 0);
}

void bmTexture2d::use() const
{
	glBindTexture(GL_TEXTURE_2D, id);
}
