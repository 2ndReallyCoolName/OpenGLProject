#pragma once
#include "stb_image.h"
#include <glad/glad.h>
#include <string>

class Texture
{
public:
	Texture(std::string fpath);
	void BindTexture(unsigned int location);

	unsigned int GetTextureID() {
		return texture;
	}

private:
	unsigned int texture = 0;
};
