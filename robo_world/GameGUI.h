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


class LightSettingsGuiWindow :public GOGuiWindow
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