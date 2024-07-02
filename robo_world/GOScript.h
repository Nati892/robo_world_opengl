#pragma once
#include "stdafx.h"
#include "GameObject.h"
class GameObject;

class GOScript
{
private:
	GameObject* _GameObject = nullptr;
	bool _started = false;//runner of script should set this to true, and aklso check this before running script Setup method

	virtual void SSetup();
public:
	~GOScript();
	void CleanUp();
	virtual void SCleanUp();
	virtual void SLoop();

	void SetupOnce();//called by script object creator

	GameObject* GetGameObject();
	void SetGameObjectOnce(GameObject*);
};