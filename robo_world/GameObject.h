#pragma once
#include "stdafx.h"
#include "GOLightSourceData.h"


class GODrawable;
class GOScript;
class GOTransform;
class Scene;
class GOLightSourceData;

enum GOType
{
	regular,
	GOCamPoint,
	GOCamLookAtPoint,
	GOLightSource,
	GOSpecialGeneral
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
	glm::vec3 _claculated_world_position;
	Scene* _attached_scene;
public:
	GameObject(GameObject* parent, std::string NewName, GOTransform* transform);
	GameObject(GameObject* parent, std::string NewName);
	~GameObject();

	//when called it destroys the script,transform and drawable.
	// if you want to keep the properties, you must first do a set...(nullptr)
	// but then it is your responsibility to destroy the objects!
	//when deep is set then it does so for all children
	void Destroy(bool deep);

	//name get/set
	std::string GetName();
	void SetName(std::string);

	//script get/set
	void SetGOScript(GOScript*);//creates a script instance (c++ object) for this child
	GOScript* GetRunningScript();

	//transform get/set
	GOTransform* GetTransform();
	GOTransform* GetTransformSafe();
	void SetTransform(GOTransform* set_trans);

	//drawable get/set
	GODrawable* GetDrawableObject();
	void SetDrawableObject(GODrawable* newDrawObj);

	Scene* GetCurrentScene();
	void SetCurrentScene(Scene*);
	//GoType
	/// <summary>
	/// sets the object type and returns if able to set it or note,
	/// can returns false if its a light source and that there is no room
	/// </summary>
	/// <param name=""></param>
	/// <returns></returns>
	bool SetGOType(GOType);
	GOType GetGoType();

	//light source data
	GOLightSourceData* GetLightSourceData();//gives out pointer to light source data
	void  SetLightSourceData(GOLightSourceData* data);//gives out pointer to light source data
	bool IsLightSource();

	//calculatedLoc
	glm::vec3 GetCalculatedLocation();
	void SetCalculatedPosition(glm::vec3);

	// children get/add
	std::vector<GameObject*>& getChildren();
	void AddChildObject(GameObject* child);

	void RemoveChildObject(GameObject* child);

	/// <summary>
	/// old ones get deleted!
	/// </summary>
	/// <param name="new_attach"></param>
	void AttachDrawable(GODrawable* new_attach);

	/// <summary>
	/// old ones get deleted!
	/// </summary>
	/// <param name="new_attach"></param>
	void AttachScript(GOScript* new_attach);

	/// <summary>
	/// old ones get deleted!
	/// </summary>
	/// <param name="new_attach"></param>
	void AttachTransform(GOTransform* new_attach);

	GameObject* GetParent();
	void SetParent(GameObject* parent);
	void CalculateWorldPosition();
};