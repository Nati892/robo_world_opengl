#pragma once
#include "stdafx.h"
#include "GameObject.h"
class GameObject;

class GOTransform {
private:
	GameObject* _GameObject = nullptr;
	GOvec3 Position = { 0,0,0 }; // x, y, z location
	GOvec3 Rotation = { 0,0,0 }; // rotation around x, y, z axis
	GOvec3 Scale = { 1,1,1 };
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
	GOvec3 GetPosition();
	GOvec3 GetRotation();
	GOvec3 GetScale();
};
