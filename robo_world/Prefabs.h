//this class has ready objects so that scene setup will be more clean to read and easier to grow.
//in future add read from standard assets(but that will come with a migration to vulkan and a full upgrade to modern stuff and cross operability)

#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Prefabs
{
public:
	//rotating objects
	static GameObject* GetNewRotatingCube(std::string name);
	static GameObject* GetNewRotatingSphere(std::string name);

	//lights
	static GameObject* GetReadyLightSource();
	static GameObject* GetReadyAmbiantLightSource();
	static GameObject* GetReadyDiffuseLightSource();
	static GameObject* GetReadySpecularLightSource();

	//non-moving objects
	static GameObject* GetReadyCubeGameObject();
	static GameObject* GetReadySurface2d();
	static GameObject* GetReadyDynamicSurface2d();
	static GameObject* GetNewSphere(std::string name);
};


