#pragma once
class bmTexture2d
{
public:
	bmTexture2d();

	const unsigned int& getId() const { return id; }

	void create(unsigned int width, unsigned int height, unsigned char * textureData);

	void use() const;

private:
	unsigned int id;

	unsigned int width;
	unsigned int height;
	unsigned int internalFormat;
	unsigned int imageFormat;
	unsigned int filterUpscale;
	unsigned int filterDownscale;

	unsigned int wrapS;
	unsigned int wrapT;
};

