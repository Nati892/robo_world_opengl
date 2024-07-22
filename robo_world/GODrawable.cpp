#include "GODrawable.h"

GODrawable::GODrawable() {
}

GODrawable::~GODrawable()
{
}

void GODrawable::CleanUp()
{
	//clear script from the game object
	GameObject* this_go = this->GetGameObject();
	if (this_go != nullptr)
	{
		GODrawable* go_atrib = this_go->GetDrawableObject();
		if (this == go_atrib)
		{
			this_go->SetDrawableObject(nullptr);
		}
	}
	delete this;
}

void GODrawable::DrawObject()
{
	printf("DrawableObject called from papa,does nothing");
}

void GODrawable::SetActiveMat() const
{
	GOMaterial::SetActiveMaterial(this->material,-1);
}

GameObject* GODrawable::GetGameObject()
{

	return this->_GameObject;
}

void GODrawable::SetGameObjectOnce(GameObject* go_head)
{
	if (this->_GameObject == nullptr)
		this->_GameObject = go_head;
}

void GODrawable::setAmbientColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	material.AmbientColor.x = r;
	material.AmbientColor.y = g;
	material.AmbientColor.z = b;
	material.AmbientColor.w = a;
}

void GODrawable::setDiffuseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	material.DiffuseColor.x = r;
	material.DiffuseColor.y = g;
	material.DiffuseColor.z = b;
	material.DiffuseColor.w = a;
}

void GODrawable::setSpecularColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	material.SpecularColor.x = r;
	material.SpecularColor.y = g;
	material.SpecularColor.z = b;
	material.SpecularColor.w = a;
}

void GODrawable::setShininess(GLfloat shininess) {
	material.Shininess[0] = shininess;
}

GOvec4 GODrawable::getAmbientColor() {
	return material.AmbientColor;
}

GOvec4 GODrawable::getDiffuseColor() {
	return material.DiffuseColor;
}

GOvec4 GODrawable::getSpecularColor() {
	return material.SpecularColor;
}

GLfloat GODrawable::getShininess() {
	return material.Shininess[0];
}


void GOMaterial::SetActiveMaterial(GOMaterial mat,int id)
{
	static int last_id=-1;
	if (id != -1 && id == last_id)
	{
		return;
	}
	last_id = id;
	float params[4] = { mat.AmbientColor.x,mat.AmbientColor.y,mat.AmbientColor.z,mat.AmbientColor.w };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, params);

	params[0] = mat.DiffuseColor.x;
	params[1] = mat.DiffuseColor.y;
	params[2] = mat.DiffuseColor.z;
	params[3] = mat.DiffuseColor.w;
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, params);

	params[0] = mat.SpecularColor.x;
	params[1] = mat.SpecularColor.y;
	params[2] = mat.SpecularColor.z;
	params[3] = mat.SpecularColor.w;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, params);

	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mat.Shininess);

}


