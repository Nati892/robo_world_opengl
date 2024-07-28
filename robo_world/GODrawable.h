#pragma once
#include "stdafx.h"
#include "GameObject.h"

struct GOMaterial
{
	glm::vec4 AmbientColor = { 1,1,1,1 }; // Ambient color (RGBA)
	glm::vec4 DiffuseColor = { 0,0,0,1 }; // Diffuse color (RGBA)
	glm::vec4 SpecularColor = { 0,0,0,1 }; // Specular color (RGBA)
	glm::vec4 Emission = { 0,0,0,1 }; //Basic emission color (RGBA)
	GLfloat Shininess[1] = { 0 }; // Shininess factor
	static void SetActiveMaterial(GOMaterial, int);

	bool operator==(GOMaterial other)
	{
		return	(
			this->AmbientColor == other.AmbientColor &&
			this->DiffuseColor == other.DiffuseColor &&
			this->SpecularColor == other.SpecularColor &&
			this->Emission == other.Emission &&
			this->Shininess == other.Shininess
			);
	}
};

class GODrawable {
private:
	GameObject* _GameObject = nullptr;

protected:
	GOMaterial material;

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
	void setEmission(GLfloat r, GLfloat g, GLfloat b, GLfloat a);
	void setShininess(GLfloat shininess);
	glm::vec4 getAmbientColor();
	glm::vec4 getDiffuseColor();
	glm::vec4 getSpecularColor();
	GLfloat getShininess();
	glm::vec4 getEmission();
};