#include "GOTransform.h"

GOTransform::GOTransform()
{
	Position.x = 0;
	Position.y = 0;
	Position.z = 0;

	Rotation.x = 0;
	Rotation.y = 0;
	Rotation.z = 0;

	Scale.x = 1;
	Scale.y = 1;
	Scale.z = 1;
}

GOTransform::GOTransform(GameObject* parent)
{
	this->_GameObject = parent;
	Position.x = 0;
	Position.y = 0;
	Position.z = 0;

	Rotation.x = 0;
	Rotation.y = 0;
	Rotation.z = 0;

	Scale.x = 1;
	Scale.y = 1;
	Scale.z = 1;
}

void GOTransform::CleanUp()
{
	//clear script from the game object
	GameObject* this_go = this->GetGameObject();
	if (this_go != nullptr)
	{
		GOTransform* go_tr = this_go->GetTransform();
		if (this == go_tr)
		{
			this_go->SetTransform(nullptr);
		}
	}
	delete this;
}

void GOTransform::setPosition(GLfloat x, GLfloat y, GLfloat z) {
	Position.x = x;
	Position.y = y;
	Position.z = z;
}

void GOTransform::setRotation(GLfloat x, GLfloat y, GLfloat z) {
	Rotation.x = x;
	Rotation.y = y;
	Rotation.z = z;
}

void GOTransform::setScale(GLfloat x, GLfloat y, GLfloat z) {
	Scale.x = x;
	Scale.y = y;
	Scale.z = z;
}
GOvec3 GOTransform::GetPosition() {
	return Position;
}

GOvec3 GOTransform::GetRotation() {
	return Rotation;
}

GOvec3 GOTransform::GetScale() {
	return Scale;
}

GameObject* GOTransform::GetGameObject()
{
	return this->_GameObject;
}

void GOTransform::SetGameObjectOnce(GameObject* go_head)
{
	if (this->_GameObject == nullptr)
		this->_GameObject = go_head;
}

void GOTransform::PushObjectTransformMatrix()
{
	glPushMatrix();
	glTranslatef(this->Position.x, this->Position.y, this->Position.z);
	glRotatef(this->Rotation.z, 0, 0, 1);
	glRotatef(this->Rotation.y, 0, 1, 0);
	glRotatef(this->Rotation.x, 1, 0, 0);
	glScalef(this->Scale.x, this->Scale.y, this->Scale.z);
}

void GOTransform::PopObjectTransformMatrix()
{
	glPopMatrix();
}
