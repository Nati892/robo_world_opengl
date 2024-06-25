#pragma once
#include "stdafx.h"
//#include "GODrawable.h"
//#include "GOScript.h"
//#include "GOTransform.h"

class GODrawable;
class GOScript;
class GOTransform;

class GameObject {

protected:
	GameObject* _parent;
	std::string _name;
	GODrawable* _DrawableObject;
	GOScript* _script;
	GOTransform* _transoform;

public:
	GameObject(GameObject* parent, std::string NewName, GOTransform* transform);
	~GameObject();

	void SetGOScript(GOScript*);//creates a script instance (c++ object) for this child

	std::vector<GameObject*> children; // Vector to hold pointers to child objects

	GOScript* GetRunningScript();

	GOTransform* GetTransform();
	void SetTransform(GOTransform* set_trans);

	GODrawable* GetDrawableObject();
	void SetDrawableObject(GODrawable* newDrawObj);

	// Method to get the vector of children objects
	std::vector<GameObject*>& getChildren();
	void addChildObject(GameObject* child);
};