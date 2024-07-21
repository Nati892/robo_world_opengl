#pragma once
#include "stdafx.h"
#include "GOScript.h"
#include "AnimationTimer.h"
#include "GameObject.h"
#include "GOTransform.h"
#include "GODrawable.h"
//write game script headers here

class GOInputSystem;
class DynamicSurfaceScript;
enum axis
{
	axis_x,
	axis_y,
	axis_z,
};

class BasicAxisRotateScript :public GOScript
{
private:
	AnimationTimer* rotate_timer;
	AnimationTimer* color_timer;
	axis _rotation_axis = axis_x;
	//virtual inherited
	void SSetup(Scene* CurrScene);
public:
	//virtual inherited
	void SLoop();
	void SCleanUp();

	void SetRotationAxis(axis a);
};

class Camera3rdPerson :public GOScript
{
private:
	Scene* this_scene;
	GOInputSystem* this_input_sys;
	GameObject* CamObject;
	GameObject* LookAtObject;
	GameObject* DynamicSurface;
	GameObject* FollowObject;
	GOTransform* FollowObjectTrans;	
	GameObject* MoveObject;
	GOTransform* MoveObjectTrans;
	DynamicSurfaceScript* CurrDynamicSurfaceScript;
	float y_axis_limit = 50.0f;
	float speed;
	void SSetup(Scene* CurrScene);
public:
	//virtual inherited
	void SLoop();
	void SCleanUp();

};



class DynamicSurfaceScript :public GOScript
{
private:
	
	GOvec3 _Scale;
	GOvec3 _Count;
	GOvec3 _Position;

	void SSetup(Scene* CurrScene);
public:
	//virtual inherited
	DynamicSurfaceScript(GOvec3 _Scale,GOvec3 _Count);
	void SLoop();
	void UpdatePosition(GOvec3 new_pos);
	void SCleanUp();

};


class SkyBoxScript :public GOScript
{
private:
	std::string FollowObjName;
	GameObject* FollowObject;
	GOTransform* FollowObjectTransform;

	void SSetup(Scene* CurrScene);
public:
	//virtual inherited
	SkyBoxScript(std::string follow_object_name);
	void SLoop();
	void SCleanUp();

};