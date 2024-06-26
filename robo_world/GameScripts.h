#pragma once
#include "stdafx.h"
#include "GOScript.h"
#include "AnimationTimer.h"
#include "GameObject.h"
#include "GOTransform.h"
#include "GODrawable.h"
//write game script headers here

enum axis
{
	axis_x,
	axis_y,
	axis_z,
};

class BasicAxisRotateScript :public GOScript
{
	AnimationTimer* rotate_timer;
	AnimationTimer* color_timer;
	axis _rotation_axis = axis_x;
public:
	//have to
	void SSetup();
	void SLoop();
	void SCleanUp();

	void SetRotationAxis(axis a);
};