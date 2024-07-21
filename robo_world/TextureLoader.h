#pragma once
#include "stdafx.h"
class TextureLoader {
private:
	static std::map<std::string, GLuint> loaded_textures;

public:
	static bool loadTexture(std::string filename,GLuint* res);
};