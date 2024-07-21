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

void DrawTeapot::DrawObject()
{
	GLuint res;
	auto texture_res = TextureLoader::loadTexture("clay_texture.jpg", &res);
//	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);
	glEnable(GL_TEXTURE_2D);        // Enable texturing
	glBindTexture(GL_TEXTURE_2D, res); // Bind the texture

	glutSolidTeapot(1);

	glDisable(GL_TEXTURE_2D);       // Disable texturing
	glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);

}

DrawTeapot::DrawTeapot()
{
	this->AmbientColor.x = 1;
	this->AmbientColor.y = 1;
	this->AmbientColor.z = 1;
	this->AmbientColor.w = 1;

	this->DiffuseColor.x = 0.6;
	this->DiffuseColor.y = 0.6;
	this->DiffuseColor.z = 0.6;
	this->DiffuseColor.w = 1;

	this->SpecularColor.x = 0.35f;
	this->SpecularColor.y = 0.35f;
	this->SpecularColor.z = 0.35f;
	this->SpecularColor.w = 1;
}


void DrawSurface2d::DrawObject() {
	if (!texture_loaded)
	{
		GLuint res = 0;
		auto texture_res = TextureLoader::loadTexture(this->texture_name, &res);
		if (texture_res)
		{
			this->TextureId = res;
		}
		else
		{
			std::cout << "error loading texture file:" << texture_name << ", set to default texture 0" << std::endl;
			this->TextureId = 0;
		}
		texture_loaded = true;
	}
	glEnable(GL_TEXTURE_2D);        // Enable texturing
	glBindTexture(GL_TEXTURE_2D, this->TextureId); // Bind the texture
	glBegin(GL_QUADS);

	glNormal3f(0, 1, 0);  // Normal is constant for the entire surface

	// Specify texture coordinates and vertex positions
	glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.5f, 0.0f, -0.5f);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.5f, 0.0f, 0.5f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(0.5f, 0.0f, 0.5f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(0.5f, 0.0f, -0.5f);

	glEnd();

	glDisable(GL_TEXTURE_2D);       // Disable texturing
}


DrawSurface2d::DrawSurface2d(std::string texture)
{
	this->texture_name = texture;
	
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