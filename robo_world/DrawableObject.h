#pragma once
#include "stdafx.h"

class DrawableObject {
private:
	GLfloat Position[3] = { 0,0,0 }; // x, y, z location
	GLfloat Rotation[3] = { 0,0,0 }; // rotation around x, y, z axis
	GLfloat Scale[3] = { 1,1,1 };
	GLfloat AmbientColor[4] = { 0,0,0,1 }; // Ambient color (RGBA)
	GLfloat DiffuseColor[4] = { 0,0,0,1 }; // Diffuse color (RGBA)
	GLfloat SpecularColor[4] = { 0,0,0,1 }; // Specular color (RGBA)
	GLfloat Shininess[1] = { 0 }; // Shininess factor
	std::vector<DrawableObject*> children; // Vector to hold pointers to child objects

public:
	DrawableObject();
	virtual ~DrawableObject(); // Declare the destructor

	virtual void DrawObject();
	void PushObjectTransformMatrix();
	void PopObjectTransformMatrix();
	void SetObjectMaterial();
	// Setters and getters for Position, Rotation, Scale
	void setPosition(GLfloat x, GLfloat y, GLfloat z);
	void setRotation(GLfloat x, GLfloat y, GLfloat z);
	void setScale(GLfloat x, GLfloat y, GLfloat z);
	GLfloat* getPosition();
	GLfloat* getRotation();
	GLfloat* getScale();

	// Setters and getters for lighting properties
	void setAmbientColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setDiffuseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setSpecularColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setShininess(GLfloat shininess);
	GLfloat* getAmbientColor();
	GLfloat* getDiffuseColor();
	GLfloat* getSpecularColor();
	GLfloat getShininess();

	//pipeline functions

	//push and pop operations

	void addChildObject(DrawableObject* child);

	// Method to get the vector of children objects
	std::vector<DrawableObject*>& getChildren();
};
