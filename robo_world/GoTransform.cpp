#include "GOTransform.h"



void GOTransform::setPosition(GLfloat x, GLfloat y, GLfloat z) {
	Position[0] = x;
	Position[1] = y;
	Position[2] = z;
}

void GOTransform::setRotation(GLfloat x, GLfloat y, GLfloat z) {
	Rotation[0] = x;
	Rotation[1] = y;
	Rotation[2] = z;
}

void GOTransform::setScale(GLfloat x, GLfloat y, GLfloat z) {
	Scale[0] = x;
	Scale[1] = y;
	Scale[2] = z;
}

GLfloat* GOTransform::getPosition() {
	return Position;
}

GLfloat* GOTransform::getRotation() {
	return Rotation;
}

GLfloat* GOTransform::getScale() {
	return Scale;
}

GameObject* GOTransform::GetGameObject()
{
	return this->_GameObject;
}

void GOTransform::PushObjectTransformMatrix()
{
	glPushMatrix();
	glTranslatef(this->Position[0], this->Position[1], this->Position[2]);
	glRotatef(this->Rotation[0], 1, 0, 0);
	glRotatef(this->Rotation[1], 0, 1, 0);
	glRotatef(this->Rotation[2], 0, 0, 1);
	glScalef(this->Scale[0], this->Scale[1], this->Scale[2]);
}

void GOTransform::PopObjectTransformMatrix()
{
	glPopMatrix();
}
