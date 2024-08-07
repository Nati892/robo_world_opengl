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

class DrawLightSphere :public GODrawable
{

public:
	void DrawObject();
	DrawLightSphere();
};

class DrawWheel :public GODrawable
{
	bool texture_loaded = false;
	GLuint TextureId;
	std::string texture_name;
public:
	void DrawObject();
	DrawWheel(std::string texture);
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

class DrawCheckBoardSurface2d : public GODrawable
{

private:
public:
	void DrawObject();
	DrawCheckBoardSurface2d();
};

class DrawMonkey :public GODrawable
{
	std::vector<Vertex>* ModelVector;
	GLuint model_texture;
public:
	void DrawObject();
	DrawMonkey();
};

class GoDrawble3d :public GODrawable {
	std::string obj_model_name;
	std::string texture_name;
	bool hasTexture = false;
	std::vector<Vertex>* ModelVector;

	std::map<int, GOMaterial> Loaded_Materials;
	GLuint model_texture;

	bool display_list_initialized = false;
	GLuint displayList_id = 0;
	static GLuint id_giver;
	std::vector<std::string> texture_names;
	std::vector<std::pair<bool, GLuint>> texture_ids;
public:
	void DrawObject();
	GoDrawble3d(std::string obj_model_name, std::string texture_name, std::vector<std::string> mat_textures = std::vector<std::string>());
};
