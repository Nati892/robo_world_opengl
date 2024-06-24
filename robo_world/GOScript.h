#include "stdafx.h"
class GameObject;

class GOScript
{
private:
	GameObject* _GameObject = nullptr;

public:

	virtual void LoopUpdate();
	virtual void SetupGameObject();
	GameObject* GetGameObject();

};