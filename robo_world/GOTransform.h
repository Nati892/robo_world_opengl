#pragma once
#include "stdafx.h"
#include "GameObject.h"
class GameObject;

class GOTransform {
private:
	GameObject* _GameObject = nullptr;
	GLfloat Position[3] = { 0,0,0 }; // x, y, z location
	GLfloat Rotation[3] = { 0,0,0 }; // rotation around x, y, z axis
	GLfloat Scale[3] = { 1,1,1 };
public:
	GOTransform();
	GOTransform(GameObject* parent);
	void CleanUp();
	GameObject* GetGameObject();
	void SetGameObjectOnce(GameObject*);

	void PushObjectTransformMatrix();
	void PopObjectTransformMatrix();

	// Setters and getters for Position, Rotation, Scale
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setRotation(GLfloat x, GLfloat y, GLfloat z);
	void setScale(GLfloat x, GLfloat y, GLfloat z);
	GLfloat* getPosition();
	GLfloat* getRotation();
	GLfloat* getScale();
};
