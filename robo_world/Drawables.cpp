#include "Drawables.h"


//cube
void DrawCube::DrawObject()
{
	glutSolidCube(1);
}

DrawCube::DrawCube()
{
	this->AmbientColor[0] = 1;
	this->AmbientColor[1] = 1;
	this->AmbientColor[2] = 1;
	this->AmbientColor[3] = 1;

	this->DiffuseColor[0] = 1;
	this->DiffuseColor[1] = 1;
	this->DiffuseColor[2] = 1;
	this->DiffuseColor[3] = 1;

	this->SpecularColor[0] = 0;
	this->SpecularColor[1] = 0;
	this->SpecularColor[2] = 0;
	this->SpecularColor[3] = 1;
}

//sphere
void DrawSphere::DrawObject()
{
	glutSolidSphere(1,20,20);
}

DrawSphere::DrawSphere()
{
	this->AmbientColor[0] = 1;
	this->AmbientColor[1] = 1;
	this->AmbientColor[2] = 1;
	this->AmbientColor[3] = 1;

	this->DiffuseColor[0] = 1;
	this->DiffuseColor[1] = 1;
	this->DiffuseColor[2] = 1;
	this->DiffuseColor[3] = 1;

	this->SpecularColor[0] = 0;
	this->SpecularColor[1] = 0;
	this->SpecularColor[2] = 0;
	this->SpecularColor[3] = 1;
}
