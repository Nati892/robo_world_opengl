#pragma once
#include "stdafx.h"

class Vertex {
public:
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoord;
};



class TextureLoader {
private:
	static std::map<std::string, GLuint> loaded_textures;

public:
	static bool loadTexture(std::string filename,GLuint* res);
};



class OBJLoader
{
private:
	static std::map<std::string, std::vector<Vertex>*> loaded_objects;
public:
	static bool MyLoadOBJ(std::string, std::vector<Vertex>** out_vertices);
};