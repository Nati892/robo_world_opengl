#include "Drawables.h"


//cube
void DrawCube::DrawObject()
{
	glutSolidCube(1);
}

DrawCube::DrawCube()
{
	this->AmbientColor.x = 1;
	this->AmbientColor.y = 0.4;
	this->AmbientColor.z = 0.4;
	this->AmbientColor.w = 1;

	this->DiffuseColor.x = 1;
	this->DiffuseColor.y = 0.4;
	this->DiffuseColor.z = 0.4;
	this->DiffuseColor.w = 1;

	this->SpecularColor.x = 0;
	this->SpecularColor.y = 0.4;
	this->SpecularColor.z = 0.4;
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

	this->SpecularColor.x = 0.35f;
	this->SpecularColor.y = 0.35f;
	this->SpecularColor.z = 0.35f;
	this->SpecularColor.w = 1;
}

void DrawSurface2d::DrawObject()
{
	glColor3f(1, 0, 0);

	float step = 2.0f / axiscuts;  // Step size between each vertex

	glBegin(GL_QUADS);
	glNormal3f(0, 1, 0);  // Normal is constant for the entire surface

	for (int i = 0; i < axiscuts; ++i) {
		for (int j = 0; j < axiscuts; ++j) {
			// Calculate vertex positions based on current slice indices
			float x0 = -1.0f + j * step;
			float z0 = -1.0f + i * step;
			float x1 = x0 + step;
			float z1 = z0 + step;

			// Define vertices of the current quad
			glVertex3f(x0, 0, z0);
			glVertex3f(x0, 0, z1);
			glVertex3f(x1, 0, z1);
			glVertex3f(x1, 0, z0);
		}
	}

	glEnd();
}

//
//void DrawSurface2d::DrawObject()
//{
//	glColor3f(1, 0, 0);
//	glBegin(GL_QUADS);
//	glNormal3f(0, 1, 0);
//	//for here and fix the quad rendering
//	glVertex3f(-1, 0, -1);
//	glVertex3f(-1, 0, 1);
//	glVertex3f(1, 0, 1);
//	glVertex3f(1, 0, -1);
//	glEnd();
//}

DrawSurface2d::DrawSurface2d()
{
	this->AmbientColor.x = 1;
	this->AmbientColor.y = 1;
	this->AmbientColor.z = 1;
	this->AmbientColor.w = 1;

	this->DiffuseColor.x = 1;
	this->DiffuseColor.y = 1;
	this->DiffuseColor.z = 1;
	this->DiffuseColor.w = 1;

	this->SpecularColor.x = 1;
	this->SpecularColor.y = 1;
	this->SpecularColor.z = 1;
	this->SpecularColor.w = 1;

	this->Shininess[0] = 0;

}

DrawSurface2d::DrawSurface2d(int cuts)
{
	axiscuts = cuts;
}
