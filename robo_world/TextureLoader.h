#pragma once
#include "stdafx.h"
#include "include/stb_image.h"
class TextureLoader {
private:
	static std::map<std::string, GLuint> loaded_textures;

public:
	static GLuint loadTexture(std::string filename);
};