#pragma once
#include "stdafx.h"
#include "GOScript.h"
#include "AnimationTimer.h"
#include "GameObject.h"
#include "GOTransform.h"
#include "GODrawable.h"
//write game script headers here

class BasicXRotateScript :public GOScript 
{
	AnimationTimer* rotate_timer;
	AnimationTimer* color_timer;

	void SSetup();
	void SLoop();
	//add cleanup func for 
};