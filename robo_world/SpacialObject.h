#pragma once
#include "stdafx.h"

class SpacialObject {
private:
	GLfloat Position[3]; // x, y, z location
	GLfloat Rotation[3]; // rotation around x, y, z axis
	GLfloat Scale[3];
	GLfloat AmbientColor[4]; // Ambient color (RGBA)
	GLfloat DiffuseColor[4]; // Diffuse color (RGBA)
	GLfloat SpecularColor[4]; // Specular color (RGBA)
	GLfloat Shininess; // Shininess factor
	std::vector<SpacialObject*> children; // Vector to hold pointers to child objects

public:
	SpacialObject();

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



	void addChildObject(SpacialObject* child);

	// Method to get the vector of children objects
	std::vector<SpacialObject*>& getChildren();
};
