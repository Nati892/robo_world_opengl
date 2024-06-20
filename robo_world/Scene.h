#pragma once
#include "stdafx.h"
#include "DrawableObject.h"
#include "SceneObjects.h"

class Scene
{
private:
	std::vector<DrawableObject*> SceneObjects;

public:
	void AddDrawableObject(DrawableObject* obj);
	void DrawScene();
	std::vector<DrawableObject*> GetChildren();
};

Scene* GetTestScene();
void DrawObjTree(DrawableObject* a);