#pragma once
#include "stdafx.h"
class GameObject;

class GOScript
{
private:
	GameObject* _GameObject = nullptr;
	bool _started = false;//runner of script should set this to true, and aklso check this before running script Setup method

	virtual void SSetup();
public:
	void SetupOnce();
	virtual void SLoop();
	//TODO: add cleanup func
	GameObject* GetGameObject();
	void SetGameObjectOnce(GameObject*);

};