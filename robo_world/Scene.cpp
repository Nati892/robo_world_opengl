#include "Scene.h"

Scene* GetTestScene()
{
	Scene* ret = new Scene();
	CubeObject* MainCube = new CubeObject();
	MainCube->setAmbientColor(0.8, 0.8, 0, 0.8);
	MainCube->setDiffuseColor(0.8, 0.8, 0, 0.8);
	ret->AddDrawableObject(MainCube);

	CubeObject* childCube = new CubeObject();
	childCube->setAmbientColor(0, 0.8, 0.8, 0.8);
	childCube->setDiffuseColor(0, 0.8, 0.8, 0.8);
	childCube->setPosition(0.5, 0.8, 0.8);
	MainCube->addChildObject(childCube);

	CubeObject* childCube2 = new CubeObject();
	childCube2->setAmbientColor(0, 0.8, 0.8, 0.8);
	childCube2->setDiffuseColor(0, 0.8, 0.8, 0.8);
	childCube2->setPosition(-0.5, 0.8, 0.8);
	MainCube->addChildObject(childCube2);

	CubeObject* childCube3 = new CubeObject();
	childCube3->setAmbientColor(0, 0.8, 0.8, 0.8);
	childCube3->setDiffuseColor(0, 0.8, 0.8, 0.8);
	childCube3->setPosition(0.8, 0.5, 0.8);
	MainCube->addChildObject(childCube3);

	CubeObject* childCube4 = new CubeObject();
	childCube4->setAmbientColor(0, 0.8, 0.8, 0.8);
	childCube4->setDiffuseColor(0, 0.8, 0.8, 0.8);
	childCube4->setPosition(0.8, -0.5, 0.8);
	MainCube->addChildObject(childCube4);
	return ret;
}

void Scene::AddDrawableObject(DrawableObject* obj)
{
	if (obj != nullptr)
		this->SceneObjects.push_back(obj);
}

void Scene::DrawScene()
{
	DrawableObject* drawObj;
	for (int i = 0; i < this->SceneObjects.size(); i++)
	{
		drawObj = SceneObjects.at(i);
		DrawObjTree(drawObj);
	}
}

std::vector<DrawableObject*> Scene::GetChildren()
{
	return this->SceneObjects;
}

void DrawObjTree(DrawableObject* a)
{
	if (a == nullptr)
		return;
	a->PushObjectTransformMatrix();
	a->SetObjectMaterial();
	a->DrawObject();
	auto children = a->getChildren();

	for (int i = 0; i < children.size(); i++)
	{
		DrawableObject* curr_child = children.at(i);
		DrawObjTree(curr_child);
	}

	a->PopObjectTransformMatrix();
}
