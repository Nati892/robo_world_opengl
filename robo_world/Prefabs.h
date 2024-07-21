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
	static GameObject* GetNewRotatingteapot(std::string name);

	//lights
	static GameObject* GetReadyLightSource(std::string name);
	static GameObject* GetReadyAmbiantLightSource(std::string name);
	static GameObject* GetReadyDiffuseLightSource(std::string name);
	static GameObject* GetReadySpecularLightSource(std::string name);

	//non-moving objects
	static GameObject* GetReadyCubeGameObject(std::string name);
	static GameObject* GetReadyTeapot(std::string name);
	static GameObject* GetReadySurface2d( std::string name, std::string texture);
	static GameObject* GetReadyDynamicSurface2d(std::string name);
	static GameObject* GetReadySkyBox( std::string name,std::string FollowObject );
	static GameObject* GetNewSphere(std::string name);
};


