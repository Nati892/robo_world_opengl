#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GODrawable.h"
#include "GOTransform.h"
#include "GOScript.h"
#include "Drawables.h"
#include "GameScripts.h"
#include "Prefabs.h"


class Scene
{
private:
	std::vector<GameObject*> SceneObjects;

public:
	/// <summary>
	/// add game object to scene
	/// </summary>
	/// <param name="obj"></param>
	void AddGameObjectTree(GameObject* obj);
	void RunSceneScripts();
	void DrawScene();
	std::vector<GameObject*> GetChildren();
	void StartScene();
};

//Scene* GetTestScene();
Scene* GetSampleScene();

/// <summary>
/// runs over all game objects and applies, transforms ,material and draws the object trees in scene.
/// doenst do the scripts
/// </summary>
/// <param name="GOHead"> tun on this object and all children game objects in tree</param>
void RunGameObjectsForFrame(GameObject*);

/// <summary>
/// runs update for each script in game scene tree
/// </summary>
void RunScripts(GameObject*);


/// <summary>
/// WARNING! should only be called once for each script at begining of scene
/// starts all the scripts in the tree
/// (calls StartSCript on each object)
/// </summary>
void StartScriptsForGOTree(GameObject*);

void SetupScriptForGameObject(GameObject*);

void StartScript(GameObject*);

void SetupScriptsForGameObjectHead(GameObject* GOHead);

//TODO: add functions to run from ambient light to parent, and get parent list, and then calculate the camera location.
//	also to calculate the lookat, we do the same for a "lookat" object, where the object is relative to player, is where we look to.

