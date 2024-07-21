#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "Loaders.h"

std::map<std::string, GLuint> TextureLoader::loaded_textures; // Definition

bool TextureLoader::loadTexture(std::string filename, GLuint* res)
{

	GLuint texture = 4;
	filename = "textures/" + filename;
	auto it = loaded_textures.find(filename);
	if (it != loaded_textures.end())
	{
		if (res != nullptr)
			*res = it->second;
		return true;
	}

	int width, height, channels;
	unsigned char* image = stbi_load(filename.c_str(), &width, &height, &channels, STBI_rgb);

	if (image == nullptr) {
		printf("Error loading texture file: %s\n", filename.c_str());
		printf("Reason: %s\n", stbi_failure_reason());
		return false;
	}

	// Ensure proper alignment
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// Generate and bind texture
	glGenTextures(1, &texture);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("OpenGL error: %d\n", error);
		stbi_image_free(image);
		*res = texture;
		return true;
	}

	glBindTexture(GL_TEXTURE_2D, texture);

	// Set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Upload texture data
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	// Check for OpenGL errors
	error = glGetError();
	if (error != GL_NO_ERROR) {
		printf("OpenGL error: %d\n", error);
		stbi_image_free(image);
		return false;
	}

	// Free image data
	stbi_image_free(image);

	loaded_textures[filename] = texture;

	// Unbind texture
	glBindTexture(GL_TEXTURE_2D, 0);
	if (res != nullptr) {
		*res = texture;
	}

	return true;
}