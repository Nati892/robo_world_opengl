#include "GOTransform.h"
MatrixStack GOTransform::matrixStack;


GOTransform::GOTransform() {
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

GOTransform::GOTransform(GameObject* parent) {
	this->_GameObject = parent;
	Position = glm::vec3(0.0f, 0.0f, 0.0f);
	Rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	Scale = glm::vec3(1.0f, 1.0f, 1.0f);
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
	TransMatChanged = true;
}

void GOTransform::setRotation(GLfloat x, GLfloat y, GLfloat z) {
	Rotation.x = x;
	Rotation.y = y;
	Rotation.z = z;
	TransMatChanged = true;
}

void GOTransform::setScale(GLfloat x, GLfloat y, GLfloat z) {
	Scale.x = x;
	Scale.y = y;
	Scale.z = z;
	TransMatChanged = true;
}

void GOTransform::setPosition(glm::vec3 vec)
{
	this->Position = vec;
	TransMatChanged = true;
}

void GOTransform::setRotation(glm::vec3 vec)
{
	this->Rotation = vec;
	TransMatChanged = true;
}

void GOTransform::setScale(glm::vec3 vec)
{
	this->Scale = vec;
	TransMatChanged = true;
}

void GOTransform::setValues(GOTransform* from_other)
{
	this->setPosition(from_other->GetPosition());
	this->setRotation(from_other->GetRotation());
	this->setScale(from_other->GetScale());
}

glm::vec3 GOTransform::GetPosition() {
	return Position;
}

glm::vec3 GOTransform::GetRotation() {
	return Rotation;
}

glm::vec3 GOTransform::GetScale() {
	return Scale;
}

GameObject* GOTransform::GetGameObject()
{
	return this->_GameObject;
}

void GOTransform::SetGameObjectOnce(GameObject* go_head)
{
	if (this == nullptr) return;//In case of an uninitialized object, just a class call
	if (this->_GameObject == nullptr)
		this->_GameObject = go_head;
}

glm::mat4 GOTransform::getTransformMatrix() {
	glm::mat4 transform;
	if (TransMatChanged) {//Only calculate if have to!
		transform = glm::mat4(1.0f);
		transform = glm::translate(transform, Position);
		transform = glm::rotate(transform, glm::radians(Rotation.x), glm::vec3(1, 0, 0));
		transform = glm::rotate(transform, glm::radians(Rotation.y), glm::vec3(0, 1, 0));
		transform = glm::rotate(transform, glm::radians(Rotation.z), glm::vec3(0, 0, 1));
		transform = glm::scale(transform, Scale);
		TransMatChanged = false;
		last_transformMatrix = transform;
	}
	else
	{
		transform = last_transformMatrix;
	}
	return transform;
}


void GOTransform::PushObjectTransformMatrix() {
	glm::mat4 transform = getTransformMatrix();
	glm::mat4 currentMatrix = matrixStack.top();
	matrixStack.push(currentMatrix * transform);
	glLoadMatrixf(glm::value_ptr(matrixStack.top()));
}

void GOTransform::PopObjectTransformMatrix() {
	matrixStack.pop();
	glLoadMatrixf(glm::value_ptr(matrixStack.top()));
}
