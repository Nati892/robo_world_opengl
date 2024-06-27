#pragma once
#include "stdafx.h"
#include "GameObject.h"

class GODrawable {
private:
	GameObject* _GameObject = nullptr;

protected:
	GOvec4 AmbientColor = { 0,0,0,1 }; // Ambient color (RGBA)
	GOvec4 DiffuseColor = { 0,0,0,1 }; // Diffuse color (RGBA)
	GOvec4 SpecularColor = { 0,0,0,1 }; // Specular color (RGBA)
	GLfloat Shininess[1] = { 0 }; // Shininess factor

public:
	GODrawable();
	~GODrawable(); // Declare the destructor

	void CleanUp();
	virtual void DrawObject();
	void SetActiveMat() const;

	GameObject* GetGameObject();
	void SetGameObjectOnce(GameObject*);

	// Setters and getters for lighting properties
	void setAmbientColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setDiffuseColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setSpecularColor(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setShininess(GLfloat shininess);
	GOvec4 getAmbientColor();
	GOvec4 getDiffuseColor();
	GOvec4 getSpecularColor();
	GLfloat getShininess();
};
