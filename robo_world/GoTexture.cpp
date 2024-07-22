#include "GoTexture.h"

GOTexture::GOTexture(std::string text_name)
{
	this->TextureName = text_name;
}

GOTexture* GOTexture::CopyTexture()
{
	auto ret = new GOTexture(this->TextureName);
	ret->ISTextureSet = this->ISTextureSet;
	ret->TextureID = this->TextureID;
	return ret;
}

GLuint GOTexture::GetTextureId()
{
	if (!this->ISTextureSet)
	{
		GLuint newID = 0;
		auto load_res = TextureLoader::loadTexture(this->TextureName,&newID);
		if (load_res)
		{
			this->TextureID = newID;
			this->ISTextureSet = true;
		}
	}
	return this->TextureID;
}


