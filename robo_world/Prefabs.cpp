#include "Prefabs.h"
#include "GOTransform.h"
#include "GOScript.h"
#include "GameScripts.h"
#include "Drawables.h"
GameObject* Prefabs::GetNewRotatingCube(std::string name)
{
	GameObject* ret = nullptr;
	ret = new GameObject(nullptr, name, nullptr);

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

GameObject* Prefabs::GetNewSphere(std::string name)
{
	GameObject* ret = nullptr;

	ret = new GameObject(nullptr, name, nullptr);

	//create transform for game object
	GOTransform* trans = new GOTransform();
	ret->AttachTransform(trans);

	//attach drawable
	DrawSphere* sphere = new DrawSphere();
	ret->AttachDrawable(sphere);

	return ret;
}

GameObject* Prefabs::GetNewRotatingSphere(std::string name)
{
	GameObject* ret = nullptr;

	ret = new GameObject(nullptr, name, nullptr);

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

GameObject* Prefabs::GetReadyAmbiantLightSource()
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, "light", light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0.4,0.4,0.4,1 };
	ldata->_light_diffuse = { 0.0,0.0,0.0,1 };
	ldata->_light_specular = { 0,0,0,1 };
	return ret;
}

GameObject* Prefabs::GetReadyDiffuseLightSource()
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, "light", light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0,0,0,1 };
	ldata->_light_diffuse = { 0.6,0.6,0.6,1 };
	ldata->_light_specular = { 0,0,0,1 };
	return ret;
}

GameObject* Prefabs::GetReadySpecularLightSource()
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, "light", light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0,0,0,1 };
	ldata->_light_diffuse = { 0,0,0,1 };
	ldata->_light_specular = {0.6,0.6,0.6,1 };
	return ret;
}

GameObject* Prefabs::GetReadyLightSource()
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, "light", light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0.2,0.2,0.2,1 };
	ldata->_light_diffuse = { 0.8,0.8,0.8,1 };
	ldata->_light_specular = { 0,0,0,1 };
	return ret;
}

GameObject* Prefabs::GetReadyCubeGameObject()
{
	GOTransform* cube_trans = new GOTransform();
	GameObject* cube_obj = new GameObject(nullptr, "cube_obj", cube_trans);

	DrawCube* cube_drawable = new DrawCube();
	cube_obj->AttachDrawable(cube_drawable);
	return cube_obj;
}

GameObject* Prefabs::GetReadySurface2d() 
{
	GOTransform* surface2d_trans = new GOTransform();
	GameObject* surface2d_obj = new GameObject(nullptr, "surface2d", surface2d_trans);

	DrawSurface2d* surface2d_drawable = new DrawSurface2d();
	surface2d_obj->AttachDrawable(surface2d_drawable);
	return surface2d_obj;

}