#pragma once
#include "stdafx.h"
#include "GameObject.h"
#include "GODrawable.h"
#include "GOTransform.h"
#include "GOScript.h"
#include "Drawables.h"
#include "GameScripts.h"
#include "Prefabs.h"
#include "GOInputSystem.h"
#include "GameGUI.h"

class Scene
{
private:
	float DeltaTime = 0;
	AnimationTimer SceneTimer;
	GameObject* SceneMasterParent = nullptr;
	GameObject* LightSourcesArray[LIGHT_SOURCES_NUM] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
	GOInputSystem* SceneInputSystem = nullptr;
	std::vector<GOGuiWindow*> gui_windows;

public:
	glm::vec3 cameraPosition = glm::vec3(0, 0, 0);
	glm::vec3 cameraTarget = glm::vec3(0, 0, 0);
	glm::vec3 cameraUp = glm::vec3(0, 1, 0);

	Scene();
	~Scene();
	/// <summary>
	/// add game object to scene
	/// </summary>
	/// <param name="obj"></param>
	void AddGameObjectTree(GameObject* obj);
	void RunSceneScripts();
	void DrawScene();
	void StartScene();
	void TraverseLightSourceInObjectTree(GameObject*);
	void TraverseLightSources();
	void UpdateTime();
	GameObject* FindObjectByName(std::string);
	/// <summary>
	/// does tree traversels and retrieves the Special game objects of type :Cam,CamLookAt and lightsource with updated calculated world position
	/// </summary>
	/// <returns> a list of all the special game objects found in scene</returns>
	std::vector<GameObject*> GetSpecialGameObjects();
	std::vector<GOGuiWindow*> GetGuiWindows();
	void SetGuiWindows(std::vector<GOGuiWindow*>);
	void AddGuiWindow(GOGuiWindow* new_win);
	void RemoveGuiWindow(GOGuiWindow* new_win);
	GOInputSystem* GetSceneInputSystem();
	float GetDeltaTime();
};



//Scene* GetTestScene();
Scene* GetWorldScene();

/// <summary>manner
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

void SetupScriptsForGameObjectHead(Scene* CurrScene, GameObject* GOHead);
void InitGameObjects(Scene* CurrScene, GameObject* GOHead);

void GetAllSpecialObjectsForObjTree(GameObject* head, std::vector<GameObject*>* GOMem);

void CaculateWorldPosition(GameObject* SpecialObject);

/// <summary>
/// finds a game object with the given name and returns a pointer to it, if not then returns null
/// </summary>
GameObject* SearchObjectByNameInObjectTree(std::string, GameObject*);


