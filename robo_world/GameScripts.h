#pragma once
#include "stdafx.h"
#include "GOScript.h"
#include "AnimationTimer.h"
#include "GameObject.h"
#include "GOTransform.h"
#include "GODrawable.h"
//write game script headers here

class GOInputSystem;

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
	float y_axis_limit = 50.0f;
	float speed;
	void SSetup(Scene* CurrScene);
public:
	//virtual inherited
	void SLoop();
	void SCleanUp();

};