#pragma once
#include "stdafx.h"
#include "GODrawable.h"
#include "GOScript.h"
#include "GOTransform.h"

class GameObject {

private:
	GameObject* _parent;
	std::string _name;
	GODrawable* _DrawableObject;
	GOScript* _script;
	GOTransform* _transoform;

public:
	GameObject(GameObject* parent, std::string NewName, GOTransform* transoform);
	~GameObject();

	template <typename T>
	void SetGOScript();

	std::vector<GameObject*> children; // Vector to hold pointers to child objects

	GOScript* GetRunningScript();
	GOTransform* GetTransform();
	GODrawable* GetDrawableObject();

	// Method to get the vector of children objects
	std::vector<GameObject*>& getChildren();
	void addChildObject(GameObject* child);
};