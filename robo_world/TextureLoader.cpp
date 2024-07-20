#define STB_IMAGE_IMPLEMENTATION
#include "TextureLoader.h"

std::map<std::string, GLuint> TextureLoader::loaded_textures; // Definition

GLuint TextureLoader::loadTexture(std::string filename)
{
	GLuint texture = 0;
	auto it = loaded_textures.find(filename);
	if (it != loaded_textures.end())
	{
		return	it->second;
	}

	int width, height, channels;
	unsigned char* image = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);

	if (image == nullptr) {
		printf("Error loading texture file: %s\n", filename);
		printf("Reason: %s\n", stbi_failure_reason());
		return texture;
	}

	// Ensure proper alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate and bind texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	// Free image data
	stbi_image_free(image);

	loaded_textures[filename] = texture;
	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}
