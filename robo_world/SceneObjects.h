#pragma once
#include "stdafx.h"

enum SceneObj :int
{
	enum_Sphere = 0,
	enum_Cube,
	enum_Cone,
	enum_Torus,
	enum_Dodecahedron,
	enum_Octahedron,
	enum_Tetrahedron,
	enum_Icosahedron,
	enum_Teapot
};

void DrawBackgroundWithColor(float r, float g, float b);
void DrawText(std::string str, float x, float y);
void DrawText(float num, float x, float y);
void Draw3DAxis(bool draw_x, bool draw_y, bool draw_z);

void DrawSceneObjOctahedron();
void DrawSceneObjSphere();
void DrawSceneObjCube();
void DrawSceneObjCone();
void DrawSceneObjTorus();
void DrawSceneObjDodecohedron();
void DrawSceneObjTetrahedron();
void DrawSceneObjCosahedron();
void DrawSceneObjTeapot();