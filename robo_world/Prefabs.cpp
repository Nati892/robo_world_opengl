#include "Prefabs.h"
#include "GOTransform.h"
#include "GOScript.h"
#include "GameScripts.h"
#include "Drawables.h"
GameObject* Prefabs::GetNewRotatingCube(std::string name)
{
	GameObject* ret = nullptr;
	ret = new GameObject(nullptr, "head", nullptr);

	//create transform for game object
	GOTransform* trans = new GOTransform();
	ret->AttachTransform(trans);

	//attach drawable
	DrawCube* cube = new DrawCube();
	ret->AttachDrawable(cube);

	//attach script
	GOScript* scripty = new BasicAxisRotateScript();
	ret->AttachScript(scripty);

	return ret;
}

GameObject* Prefabs::GetNewRotatingSphere(std::string name)
{
	GameObject* ret = nullptr;

	ret = new GameObject(nullptr, "son", nullptr);

	//create transform for game object
	GOTransform* trans = new GOTransform();
	ret->AttachTransform(trans);

	//attach drawable
	DrawSphere* sphere = new DrawSphere();
	ret->AttachDrawable(sphere);

	//attach script
	GOScript* scripty = new BasicAxisRotateScript();
	ret->AttachScript(scripty);
	return ret;
}
