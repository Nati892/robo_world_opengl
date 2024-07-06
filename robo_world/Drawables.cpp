#include "Drawables.h"


//cube
void DrawCube::DrawObject()
{
	glutSolidCube(1);
}

DrawCube::DrawCube()
{
	this->AmbientColor.x = 1;
	this->AmbientColor.y = 1;
	this->AmbientColor.z = 1;
	this->AmbientColor.w = 1;

	this->DiffuseColor.x = 1;
	this->DiffuseColor.y = 1;
	this->DiffuseColor.z = 1;
	this->DiffuseColor.w = 1;

	this->SpecularColor.x = 0;
	this->SpecularColor.y = 0;
	this->SpecularColor.z = 0;
	this->SpecularColor.w = 1;
}

//sphere
void DrawSphere::DrawObject()
{
	glutSolidSphere(1, 200, 200);
}

DrawSphere::DrawSphere()
{
	this->AmbientColor.x = 0.8;
	this->AmbientColor.y = 0.4;
	this->AmbientColor.z = 0.6;
	this->AmbientColor.w = 1;

	this->DiffuseColor.x = 0.6;
	this->DiffuseColor.y = 0.3;
	this->DiffuseColor.z = 4.5;
	this->DiffuseColor.w = 1;

	this->SpecularColor.x = 0.2;
	this->SpecularColor.y = 0.2;
	this->SpecularColor.z = 0.2;
	this->SpecularColor.w = 1;
}
