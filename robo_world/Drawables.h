#pragma once
#include "stdafx.h"
#include "GODrawable.h"
#include <stb_image.h>

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

class DrawTeapot :public GODrawable
{

public:
	void DrawObject();
	DrawTeapot();
};

class DrawSurface2d : public GODrawable 
{

private:
	bool texture_loaded = false;
	GLuint TextureId;
	std::string texture_name;
public:
	void DrawObject();
	DrawSurface2d(std::string texture);
};