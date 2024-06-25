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

	glMaterialfv(GL_FRONT, GL_AMBIENT, this->AmbientColor);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, this->DiffuseColor);
	glMaterialfv(GL_FRONT, GL_SPECULAR, this->SpecularColor);
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
	AmbientColor[0] = r;
	AmbientColor[1] = g;
	AmbientColor[2] = b;
	AmbientColor[3] = a;
}

void GODrawable::setDiffuseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	DiffuseColor[0] = r;
	DiffuseColor[1] = g;
	DiffuseColor[2] = b;
	DiffuseColor[3] = a;
}

void GODrawable::setSpecularColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a) {
	SpecularColor[0] = r;
	SpecularColor[1] = g;
	SpecularColor[2] = b;
	SpecularColor[3] = a;
}

void GODrawable::setShininess(GLfloat shininess) {
	Shininess[0] = shininess;
}

GLfloat* GODrawable::getAmbientColor() {
	return AmbientColor;
}

GLfloat* GODrawable::getDiffuseColor() {
	return DiffuseColor;
}

GLfloat* GODrawable::getSpecularColor() {
	return SpecularColor;
}

GLfloat GODrawable::getShininess() {
	return Shininess[0];
}


