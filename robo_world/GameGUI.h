#pragma once
#include "stdafx.h"

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
	GOvec3 light_data;

private:
	bool quit_clicked = false;

public:
	virtual void CleanUp();
	void ShowGUI(Scene* current_scene);
};
