#pragma once
#include "stdafx.h"

class GameObject;

class GODrawable {
private:
GameObject* _GameObject = nullptr;

	GLfloat AmbientColor[4] = { 0,0,0,1 }; // Ambient color (RGBA)
	GLfloat DiffuseColor[4] = { 0,0,0,1 }; // Diffuse color (RGBA)
	GLfloat SpecularColor[4] = { 0,0,0,1 }; // Specular color (RGBA)
	GLfloat Shininess[1] = { 0 }; // Shininess factor

public:
	GODrawable();
	virtual ~GODrawable(); // Declare the destructor

	virtual void DrawObject();
	void SetActiveMat();

	// Setters and getters for lighting properties
	void setAmbientColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setDiffuseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setSpecularColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setShininess(GLfloat shininess);
	GLfloat* getAmbientColor();
	GLfloat* getDiffuseColor();
	GLfloat* getSpecularColor();
	GLfloat getShininess();

	
};
