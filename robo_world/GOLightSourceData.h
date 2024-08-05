#pragma once
#include "stdafx.h"
#include "GameObject.h"

class GOLightSourceData
{
public:
	int light_source_number = -1;
	glm::vec4 _light_ambient = { 1.0f, 1.0f,  1.0f, 1.0 };  // Ambient light
	glm::vec4 _light_diffuse = { 1.0f,  1.0f,  1.0f, 1.0 };  // Diffuse light
	glm::vec4 _light_specular = { 1.0f,  1.0f,  1.0f, 1.0 };  // Diffuse light
	glm::vec3 _spot_direction = { 0.0f, 0.0f, 0.0f };
	GLfloat _spotlight_cuttoff = 180.0f;
	GLfloat _shininess = 0.0f;
	GLfloat _exponent = 3;

	void SetData(GOLightSourceData* other);
};
