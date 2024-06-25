#include "Scene.h"
Scene* GetSampleScene()
{
	//create scene
	Scene* ret = new Scene();

	GameObject* Base = Prefabs::GetNewRotatingCube("Papa1");
	Base->GetTransform()->setPosition(2, 0, 0);
	dynamic_cast<BasicAxisRotateScript*>(Base->GetRunningScript())->SetRotationAxis(axis_z);

	GameObject* child1 = Prefabs::GetNewRotatingSphere("child1");
	child1->GetTransform()->setPosition(1, 1, 1);

	Base->addChildObject(child1);

	GameObject* Base2 = Prefabs::GetNewRotatingSphere("Papa2");
	Base2->GetTransform()->setPosition(-2, 0, 0);

	GameObject* child2 = Prefabs::GetNewRotatingCube("child2");
	child2->GetTransform()->setPosition(1, 1, -1);
	Base2->addChildObject(child2);

	ret->AddGameObjectTree(Base);
	ret->AddGameObjectTree(Base2);

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