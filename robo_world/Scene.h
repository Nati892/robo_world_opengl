#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GODrawable.h"

class Scene
{
private:
	std::vector<GameObject*> SceneObjects;

public:
	void AddGameObject(GameObject* obj);
	void DrawScene();
	std::vector<GameObject*> GetChildren();
};

//Scene* GetTestScene();
void DrawObjTree(GameObject* a);