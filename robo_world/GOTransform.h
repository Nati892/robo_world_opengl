#pragma once
#include "stdafx.h"
#include "GameObject.h"
class GameObject;

class GOTransform {
private:
	GameObject* _GameObject = nullptr;
	glm::vec3 Position = { 0,0,0 }; // x, y, z location
	glm::vec3 Rotation = { 0,0,0 }; // rotation around x, y, z axis
	glm::vec3 Scale = { 1,1,1 };
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
	void setPosition(glm::vec3);
	void setRotation(glm::vec3);
	void setScale(glm::vec3);
	void setValues(GOTransform*);
	glm::vec3 GetPosition();
	glm::vec3 GetRotation();
	glm::vec3 GetScale();
};
