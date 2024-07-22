#pragma once
#include "stdafx.h"

class GOTexture
{
	bool ISTextureSet = false;
	GLuint TextureID;
	std::string TextureName;
public:
	GOTexture(std::string);
	GOTexture* CopyTexture();
	GLuint GetTextureId();
};