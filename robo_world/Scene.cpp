#include "Scene.h"
#include "GameScripts.h"
Scene* GetSampleScene()
{
	//create scene
	Scene* ret = new Scene();

	//create 
	GameObject* Base = new GameObject(nullptr, "head", nullptr);
	ret->AddGameObjectTree(Base);

	//create transform for game object
	GOTransform* trans = new GOTransform(Base);
	Base->SetTransform(trans);

	//attach drawable
	DrCube* cube = new DrCube();
	auto asGODrawable = (static_cast<GODrawable*>(cube));

	asGODrawable->SetGameObjectOnce(Base);
	Base->SetDrawableObject(asGODrawable);

	//attach script
	auto scripty = new BasicXRotateScript();
	scripty->SetGameObjectOnce(Base);
	Base->SetGOScript(scripty);

	//set son cube
	GameObject* son = new GameObject(Base, "son", nullptr);
	Base->addChildObject(son);

	trans = new GOTransform(son);
	son->SetTransform(trans);
	trans->setPosition(1,1,1);

	//attach drawable
	cube = new DrCube();
	asGODrawable = (static_cast<GODrawable*>(cube));

	asGODrawable->SetGameObjectOnce(son);
	son->SetDrawableObject(asGODrawable);

	//attach script
	scripty = new BasicXRotateScript();
	scripty->SetGameObjectOnce(son);
	son->SetGOScript(scripty);

	return ret;
}

void Scene::AddGameObjectTree(GameObject* obj)
{
	
	if (obj != nullptr)
		this->SceneObjects.push_back(obj);
}

void Scene::StartScene()
{
	GameObject* curr_GO;
	for (int i = 0; i < this->SceneObjects.size(); i++)
	{
		curr_GO = SceneObjects.at(i);
		SetupScriptsForGameObjectHead(curr_GO);
	}
}

void Scene::RunSceneScripts()
{
	GameObject* curr_GO;
	for (int i = 0; i < this->SceneObjects.size(); i++)
	{
		curr_GO = SceneObjects.at(i);
		RunScripts(curr_GO);
	}
}

void Scene::DrawScene()
{

	GameObject* curr_GO;
	for (int i = 0; i < this->SceneObjects.size(); i++)
	{
		curr_GO = SceneObjects.at(i);
		RunGameObjectsForFrame(curr_GO);
	}
}

std::vector<GameObject*> Scene::GetChildren()
{
	return this->SceneObjects;
}

void RunScripts(GameObject* GOHead)
{
	if (GOHead == nullptr)
		return;

	//get and run script of game object
	GOScript* curr_script = GOHead->GetRunningScript();
	if (curr_script != nullptr)
	{
		curr_script->SLoop();
	}

	//run scripts for children
	auto children = GOHead->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		GameObject* curr_child = children.at(i);
		RunScripts(curr_child);
	}
}


//apply transforms, and drawables for all objects in the scene
void RunGameObjectsForFrame(GameObject* GOHead)
{
	GOTransform* _obj_trans = nullptr;
	GODrawable* _obj_Draw = nullptr;

	if (GOHead == nullptr || GOHead->GetDrawableObject() == nullptr)
		return;

	_obj_Draw = GOHead->GetDrawableObject();

	//set transform
	if (GOHead->GetTransform() != nullptr) {

		_obj_trans = GOHead->GetTransform();
		_obj_trans->PushObjectTransformMatrix();
	}

	//draw object
	if (_obj_Draw != nullptr)
	{
		_obj_Draw->SetActiveMat();
		_obj_Draw->DrawObject();
	}

	//run for children game objects
	auto children = GOHead->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		GameObject* curr_child = children.at(i);
		RunGameObjectsForFrame(curr_child);
	}

	//undo transform
	if (_obj_trans != nullptr)
		_obj_trans->PopObjectTransformMatrix();
}


void SetupScriptForGameObject(GameObject* GO_in)
{
	if (GO_in == nullptr)
		return;

	GOScript* GO_Script = GO_in->GetRunningScript();
	if (GO_Script != nullptr)
	{
		GO_Script->SetupOnce();
	}
}

void SetupScriptsForGameObjectHead(GameObject* GOHead)
{
	if (GOHead == nullptr)
		return;

	//get and run script of game object
	GOScript* curr_script = GOHead->GetRunningScript();
	if (curr_script != nullptr)
	{
		curr_script->SetupOnce();
	}

	//run scripts for children
	auto children = GOHead->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		GameObject* curr_child = children.at(i);
		SetupScriptsForGameObjectHead(curr_child);
	}
}

//another traversal func to get light distances where it goes for each light source up the parent tree and then calculates the trasforms