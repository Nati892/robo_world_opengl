#pragma once
#include "stdafx.h"
#include "GOLightSourceData.h"
class GODrawable;
class GOScript;
class GOTransform;

//this enum - GOCamPoint, GOCamLookAtPoint, GOLightSource// todo add all of them
//are helpers and basci opengl 1.1 doesnt allow to calculate my own matrices, only with some gltransform... or something like that
//this attach to objects and then get their location calculated to set normally in the scene

enum GOType
{
	regular,
	GOCamPoint,
	GOCamLookAt,
	GOLightSource
};

class GameObject {

protected:
	GameObject* _parent;
	std::string _name;
	GODrawable* _DrawableObject;
	GOScript* _script;
	GOTransform* _transoform;
	std::vector<GameObject*> children; // Vector to hold pointers to child objects
	GOType _GO_object_type = regular;
	GOLightSourceData* _light_source_data = nullptr;

public:
	GameObject(GameObject* parent, std::string NewName, GOTransform* transform);
	~GameObject();

	//when called it destroys the script,transform and drawable.
	// if you want to keep the properties, you must first do a set...(nullptr)
	// but then it is your responsibility to destroy the objects!
	//when deep is set then it does so for all children
	void Destroy(bool deep);

	//script get/set
	void SetGOScript(GOScript*);//creates a script instance (c++ object) for this child
	GOScript* GetRunningScript();

	//transform get/set
	GOTransform* GetTransform();
	void SetTransform(GOTransform* set_trans);

	//drawable get/set
	GODrawable* GetDrawableObject();
	void SetDrawableObject(GODrawable* newDrawObj);

	//old ones get destoryed
	void AttachDrawable(GODrawable* new_attach);
	void AttachScript(GOScript* new_attach);
	void AttachTransform(GOTransform* new_attach);

	//light source data
	void SetGOType(GOType, int light_number = 0);//sets 
	GOLightSourceData* GetLightSourceData();//gives out pointer to light source data
	bool IsLightSource();

	// children get/add
	std::vector<GameObject*>& getChildren();
	void addChildObject(GameObject* child);
};