//this class has ready objects so that scene setup will be more clean to read and easier to grow.
//in future add read from standard assets(but that will come with a migration to vulkan and a full upgrade to modern stuff and cross operability)

#pragma once
#include "stdafx.h"
#include "GameObject.h"

class Prefabs
{
public:
	static GameObject* GetNewRotatingCube(std::string name);
	static GameObject* GetNewRotatingSphere(std::string name);


	static GameObject* GetReadyLightSource();

};


