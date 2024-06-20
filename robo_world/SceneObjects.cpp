#include "SceneObjects.h"

CubeObject::CubeObject()
{
	this->setAmbientColor(0.4, 1, 0.4, 1);
	this->setDiffuseColor(0.2, 0.5, 0.2, 1);
	this->setSpecularColor(1, 1, 1, 1);
}

CubeObject::~CubeObject()
{
}

void CubeObject::DrawObject()
{
	glutSolidCube(1);
}
