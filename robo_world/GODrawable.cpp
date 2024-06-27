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
	float params[4] = { this->AmbientColor.x,this->AmbientColor.y,this->AmbientColor.z,this->AmbientColor.w };
	glMaterialfv(GL_FRONT, GL_AMBIENT, params);

	params[0] = this->DiffuseColor.x;
	params[1] = this->DiffuseColor.y;
	params[2] = this->DiffuseColor.z;
	params[3] = this->DiffuseColor.w;
	glMaterialfv(GL_FRONT, GL_DIFFUSE, params);

	params[0] = this->SpecularColor.x;
	params[1] = this->SpecularColor.y;
	params[2] = this->SpecularColor.z;
	params[3] = this->SpecularColor.w;
	glMaterialfv(GL_FRONT, GL_SPECULAR, params);

	glMaterialfv(GL_FRONT, GL_SHININESS, this->Shininess);
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
	AmbientColor.x = r;
	AmbientColor.y = g;
	AmbientColor.z = b;
	AmbientColor.w = a;
}

void GODrawable::setDiffuseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	DiffuseColor.x = r;
	DiffuseColor.y = g;
	DiffuseColor.z = b;
	DiffuseColor.w = a;
}

void GODrawable::setSpecularColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	SpecularColor.x = r;
	SpecularColor.y = g;
	SpecularColor.z = b;
	SpecularColor.w = a;
}

void GODrawable::setShininess(GLfloat shininess) {
	Shininess[0] = shininess;
}

GOvec4 GODrawable::getAmbientColor() {
	return AmbientColor;
}

GOvec4 GODrawable::getDiffuseColor() {
	return DiffuseColor;
}

GOvec4 GODrawable::getSpecularColor() {
	return SpecularColor;
}

GLfloat GODrawable::getShininess() {
	return Shininess[0];
}


