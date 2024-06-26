#pragma once
#include "stdafx.h"
#include "GameObject.h"

class GOLightSourceData
{
public:
	GOvec4 _light_ambient[4] = { 1.0f, 1.0f,  1.0f, 1.0 };  // Ambient light
	GOvec4 _light_diffuse[4] = { 1.0f,  1.0f,  1.0f, 1.0 };  // Diffuse light
	GOvec4 _light_zeros[4] = { 1.0f,  1.0f,  1.0f, 1.0 };  // Diffuse light
	GOvec3 _spot_direction[3] = { 0.0f, 0.0f, 0.0f };
	GLfloat _GL_SPOT_CUTOFF = 180.0f;
	GLfloat _shininess = 0.0f;
};
