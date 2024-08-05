#pragma once
#include "stdafx.h"
#include "GOTransform.h"
//Declerations
class Scene;
class GOLightSourceData;


class GOGuiWindow {
private:
public:
	virtual void CleanUp();
	virtual void ShowGUI(Scene* current_scene);
};


class MainGuiWinodw :public GOGuiWindow
{

private:
	bool help_clicked = false;
	bool quit_clicked = false;
	bool set_ambiant_light_clicked = false;
	bool set_point_light_sources_clicked = false;
	bool robot_arm_controls_clicked = false;


public:
	virtual void CleanUp();
	void ShowGUI(Scene* current_scene);
};


class HelpGuiWindow :public GOGuiWindow
{

private:
	bool quit_clicked = false;

public:
	virtual void CleanUp();
	void ShowGUI(Scene* current_scene);
};


class AmbiantLightSettingsGuiWindow :public GOGuiWindow
{
	bool light_source_searched = false;
	GOLightSourceData* p_light_data = nullptr;
	glm::vec3 light_data;
	glm::vec4 original_light_data;

private:
	bool quit_clicked = false;
	bool reset_light_clicked = false;

public:
	virtual void CleanUp();
	void ShowGUI(Scene* current_scene);
};


class PointLightSettingsGuiWindow :public GOGuiWindow
{
	bool light_source0_searched = false;
	bool light_source1_searched = false;

	GOLightSourceData* p_light_data0 = nullptr;
	GOLightSourceData* p_light_data1 = nullptr;

	GOTransform* Light0Trans = nullptr;
	GOTransform* Light1Trans = nullptr;

	glm::vec3 light_pos0;
	glm::vec3 light_pos1;

	//original data for reset buttons
	glm::vec3 original_light_position0;
	glm::vec3 original_light_position1;

	GOLightSourceData original_light_data0;
	GOLightSourceData original_light_data1;

private:
	bool quit_clicked = false;
	bool reset_light0_clicked = false;
	bool reset_light1_clicked = false;

public:
	virtual void CleanUp();
	void ShowGUI(Scene* current_scene);
};




class ArmControlSettingsGuiWindow :public GOGuiWindow
{
	bool ObjectsSearched = false;

	GOTransform* ArmTrans = nullptr;
	GOTransform* ForarmTrans = nullptr;
	GOTransform* HandTrans = nullptr;

	glm::vec3 ArmRotation;
	glm::vec3 ForarmRotation;
	glm::vec3 HandRotation;

private:
	bool quit_clicked = false;

public:
	virtual void CleanUp();
	void ShowGUI(Scene* current_scene);
};