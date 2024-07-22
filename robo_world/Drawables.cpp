#include "Drawables.h"


//cube
void DrawCube::DrawObject()
{
	glutSolidCube(1);
}

DrawCube::DrawCube()
{
	this->material.AmbientColor.x = 1;
	this->material.AmbientColor.y = 0.4;
	this->material.AmbientColor.z = 0.4;
	this->material.AmbientColor.w = 1;

	this->material.DiffuseColor.x = 1;
	this->material.DiffuseColor.y = 0.4;
	this->material.DiffuseColor.z = 0.4;
	this->material.DiffuseColor.w = 1;

	this->material.SpecularColor.x = 0;
	this->material.SpecularColor.y = 0.4;
	this->material.SpecularColor.z = 0.4;
	this->material.SpecularColor.w = 1;
}

//sphere
void DrawSphere::DrawObject()
{
	glutSolidSphere(1, 200, 200);
}

DrawSphere::DrawSphere()
{
	this->material.AmbientColor.x = 0.8;
	this->material.AmbientColor.y = 0.4;
	this->material.AmbientColor.z = 0.6;
	this->material.AmbientColor.w = 1;

	this->material.DiffuseColor.x = 0.6;
	this->material.DiffuseColor.y = 0.3;
	this->material.DiffuseColor.z = 4.5;
	this->material.DiffuseColor.w = 1;

	this->material.SpecularColor.x = 0.35f;
	this->material.SpecularColor.y = 0.35f;
	this->material.SpecularColor.z = 0.35f;
	this->material.SpecularColor.w = 1;
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
	this->material.AmbientColor.x = 1;
	this->material.AmbientColor.y = 1;
	this->material.AmbientColor.z = 1;
	this->material.AmbientColor.w = 1;

	this->material.DiffuseColor.x = 0.6;
	this->material.DiffuseColor.y = 0.6;
	this->material.DiffuseColor.z = 0.6;
	this->material.DiffuseColor.w = 1;

	this->material.SpecularColor.x = 0.35f;
	this->material.SpecularColor.y = 0.35f;
	this->material.SpecularColor.z = 0.35f;
	this->material.SpecularColor.w = 1;
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

	this->material.AmbientColor.x = 1;
	this->material.AmbientColor.y = 1;
	this->material.AmbientColor.z = 1;
	this->material.AmbientColor.w = 1;

	this->material.DiffuseColor.x = 1;
	this->material.DiffuseColor.y = 1;
	this->material.DiffuseColor.z = 1;
	this->material.DiffuseColor.w = 1;

	this->material.SpecularColor.x = 1;
	this->material.SpecularColor.y = 1;
	this->material.SpecularColor.z = 1;
	this->material.SpecularColor.w = 1;

	this->material.Shininess[0] = 0;

}

void DrawMonkey::DrawObject()
{
	if (ModelVector != nullptr) {
		std::vector<Vertex>* ret = new std::vector<Vertex>();
		bool res = OBJLoader::MyLoadOBJ("suzi.obj", &ret);
		this->ModelVector = ret;
	}

	if (ModelVector == nullptr)
		return;
	if (this->model_texture == 0)
	{
		auto text = TextureLoader::loadTexture("clay_texture.jpg", &(this->model_texture));
		if (!text)
		{
			this->model_texture = 0;
		}
	}
	glEnable(GL_TEXTURE_2D);        // Enable texturing
	glBindTexture(GL_TEXTURE_2D, this->model_texture); // Bind the texture
	glColor3f(1, 1, 1);
	glBegin(GL_TRIANGLES);
	for (const auto& vertex : *ModelVector) {
		glTexCoord2fv((float*)(&(vertex.texCoord)));
		glNormal3fv((float*)(&(vertex.normal)));
		glVertex3fv((float*)(&(vertex.position)));
	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void GoDrawble3d::DrawObject()
{
	GLuint res;
	if (ModelVector == nullptr) {
		std::vector<Vertex>* ret = new std::vector<Vertex>();
		bool res = OBJLoader::MyLoadOBJ(this->obj_model_name, &ret, &Loaded_Materials);
		this->ModelVector = ret;
	}
	if (ModelVector == nullptr)
		return;
	if (this->model_texture == 0)
	{
		auto text = TextureLoader::loadTexture(this->texture_name, &(this->model_texture));
		if (!text)
		{
			this->model_texture = 1;
		}
	}

	if (this->display_list_initialized)
	{
		glCallList(displayList_id);
		return;
	}

	this->display_list_initialized = true;
	this->displayList_id = glGenLists(1);
	glNewList(this->displayList_id, GL_COMPILE);

	if (texture_name != "")
	{
		glEnable(GL_TEXTURE_2D);        // Enable texturing
		glBindTexture(GL_TEXTURE_2D, this->model_texture); // Bind the texture
	}
	glBegin(GL_TRIANGLES);
	for (const auto& vertex : *ModelVector) {
		auto mat = Loaded_Materials[vertex.material_id];
		//GOMaterial::SetActiveMaterial(mat,vertex.material_id);
		glTexCoord2fv((float*)(&(vertex.texCoord)));
		glNormal3fv((float*)(&(vertex.normal)));
		glVertex3fv((float*)(&(vertex.position)));
	}
	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEndList();
}

GoDrawble3d::GoDrawble3d(std::string obj_model_name, std::string texture_name)
{
	std::vector<Vertex>* ret = new std::vector<Vertex>();
	this->obj_model_name = obj_model_name;
	this->texture_name = texture_name;
}

