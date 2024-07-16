#pragma once
#include "stdafx.h"
#include "GODrawable.h"


class DrawCube :public GODrawable
{

public:
	void DrawObject();
	DrawCube();
};




class DrawSphere :public GODrawable
{

public:
	void DrawObject();
	DrawSphere();
};


class DrawSurface2d : public GODrawable 
{
	int axiscuts = 100;
public:
	void DrawObject();
	DrawSurface2d();
	DrawSurface2d(int a);

};