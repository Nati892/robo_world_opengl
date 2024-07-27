#include "Scene.h"
Scene* GetSampleScene()
{
	//create scene
	Scene* ret_scene = new Scene();

	GameObject* Base = Prefabs::GetNewRotatingCube("Papa1");
	Base->GetTransform()->setPosition(2, 0, 0);
	dynamic_cast<BasicAxisRotateScript*>(Base->GetRunningScript())->SetRotationAxis(axis_z);

	GameObject* child1 = Prefabs::GetNewRotatingSphere("child1");
	child1->GetTransform()->setPosition(1, 1, 1);

	Base->addChildObject(child1);

	GameObject* Base2 = Prefabs::GetNewRotatingSphere("Papa2");
	Base2->GetTransform()->setPosition(-2, 0, 0);

	GameObject* child2 = Prefabs::GetNewRotatingCube("child2");
	child2->GetTransform()->setPosition(1, 1, -1);
	Base2->addChildObject(child2);

	ret_scene->AddGameObjectTree(Base);
	ret_scene->AddGameObjectTree(Base2);


	GOTransform* MainTrans = new GOTransform();
	GameObject* CameraHolder = new GameObject(nullptr, "CamHead", MainTrans);

	GOTransform* CamTrans = new GOTransform();
	GameObject* MainCam = new GameObject(nullptr, "MainCam", CamTrans);
	CamTrans->setPosition(0, 0, 5);
	MainCam->SetGOType(GOCamPoint);

	GOTransform* CamLookAtTrans = new GOTransform();
	GameObject* CamLookAt = new GameObject(nullptr, "MainCamLookAt", CamLookAtTrans);
	CamLookAtTrans->setPosition(0, 1, 0);
	CamLookAt->SetGOType(GOCamLookAt);

	CameraHolder->addChildObject(MainCam);
	CameraHolder->addChildObject(CamLookAt);
	ret_scene->AddGameObjectTree(CameraHolder);

	//test light source
	GameObject* LightsHolder = new GameObject(nullptr, "LightsHolder", nullptr);
	ret_scene->AddGameObjectTree(LightsHolder);

	GameObject* light0 = Prefabs::GetReadyLightSource("light0");
	GameObject* light1 = Prefabs::GetReadyLightSource("light1");
	GameObject* light2 = Prefabs::GetReadyLightSource("light2");
	GameObject* light3 = Prefabs::GetReadyLightSource("light3");

	LightsHolder->addChildObject(light0);
	LightsHolder->addChildObject(light1);
	LightsHolder->addChildObject(light2);
	LightsHolder->addChildObject(light3);

	auto l_trans = light0->GetTransform();
	l_trans->setPosition(0, 10, 0);

	l_trans = light1->GetTransform();
	l_trans->setPosition(20, 0, 0);

	l_trans = light2->GetTransform();
	l_trans->setPosition(0, 20, 10);

	l_trans = light3->GetTransform();
	l_trans->setPosition(0, -20, 10);

	return ret_scene;
}

Scene* GetWorldScene()
{
	Scene* ret_scene = new Scene();

	//add lights to scene
	GameObject* LightsHolder = new GameObject(nullptr, "LightsHolder");
	ret_scene->AddGameObjectTree(LightsHolder);

	GameObject* main_light = Prefabs::GetReadyAmbiantLightSource("main_ambiant_light");
	GameObject* sun_light = Prefabs::GetReadySunLightSource("sun_light");

	LightsHolder->addChildObject(main_light);
	LightsHolder->addChildObject(sun_light);
	main_light->GetTransform()->setPosition(0,1,1);
	sun_light->GetTransform()->setPosition(10,10,10);

	GameObject* PlayerAndCameraHolder = new GameObject(nullptr, "player_holder", nullptr);

	//add cam object
	GOTransform* CamHolderTransform = new GOTransform();
	GameObject* CameraHolder = new GameObject(nullptr, "CamHead", CamHolderTransform);
	CamHolderTransform->setPosition(0, 0, 0);

	GOTransform* CamTrans = new GOTransform();
	GameObject* MainCam = new GameObject(nullptr, "MainCam", CamTrans);
	CamTrans->setPosition(0, 7, 3);
	MainCam->SetGOType(GOCamPoint);

	GOTransform* CamLookAtTrans = new GOTransform();
	GameObject* CamLookAt = new GameObject(nullptr, "MainCamLookAt", CamLookAtTrans);
	CamLookAtTrans->setPosition(0, 2, 0);
	CamLookAt->SetGOType(GOCamLookAt);

	CameraHolder->addChildObject(MainCam);
	CameraHolder->addChildObject(CamLookAt);

	//set script to camera holder
	CameraHolder->SetGOScript(new Camera3rdPerson());

	PlayerAndCameraHolder->addChildObject(CameraHolder);
	PlayerAndCameraHolder->GetTransform()->setPosition(0, 12, 0);
	ret_scene->AddGameObjectTree(PlayerAndCameraHolder);

	auto Box = Prefabs::GetReadySkyBox("Skybox", "player_holder");
	ret_scene->AddGameObjectTree(Box);

	auto d_surface = Prefabs::GetReadyDynamicSurface2d("dynamic_surface2d");
	ret_scene->AddGameObjectTree(d_surface);

	auto robo_obj = Prefabs::GetNewRobot("player");
	PlayerAndCameraHolder->addChildObject(robo_obj);

	auto tree_ob1 = Prefabs::GetNewRandomTree("tree1");

	auto mush = Prefabs::GetNewMushroom("mushy");
	ret_scene->AddGameObjectTree(mush);

	ret_scene->AddGuiWindow(new MainGuiWinodw());

	return ret_scene;
}

void Scene::AddGameObjectTree(GameObject* obj)
{
	SceneMasterParent->addChildObject(obj);
}

//note: I know this could be implemented in a lot more efficient manner, but this is true for much of this. I just want this to work well for now, in the future I might revamp this project
GameObject* Scene::FindObjectByName(std::string object_name)
{
	auto found_obj = SearchObjectByNameInObjectTree(object_name, this->SceneMasterParent);
	return found_obj;
}

GOInputSystem* Scene::GetSceneInputSystem()
{
	return this->SceneInputSystem;
}

std::vector<GOGuiWindow*> Scene::GetGuiWindows()
{
	return this->gui_windows;
}

void Scene::AddGuiWindow(GOGuiWindow* new_win)
{
	this->gui_windows.push_back(new_win);
}

void Scene::RemoveGuiWindow(GOGuiWindow* new_win)
{
	auto it = std::find(this->gui_windows.begin(), this->gui_windows.end(),
		new_win);

	// If element is found found, erase it 
	if (it != this->gui_windows.end()) {
		it[0]->CleanUp();
		this->gui_windows.erase(it);
	}
}

void Scene::SetGuiWindows(std::vector<GOGuiWindow*> new_windows)
{
	this->gui_windows = new_windows;
}

float Scene::GetDeltaTime()
{
	return this->DeltaTime;
}

void Scene::TraverseLightSources()
{
	for (int i = 0; i < LIGHT_SOURCES_NUM; i++)
	{
		LightSourcesArray[i] = nullptr;
	}
	TraverseLightSourceInObjectTree(SceneMasterParent);
}

void Scene::UpdateTime()
{
	DeltaTime = this->SceneTimer.TimeLapseFromLastSampleMillis() / 1000;
	this->SceneTimer.SampleNow();
}

//another traversal func to get light distances where it goes for each light source up the parent tree and then calculates the trasforms
void Scene::TraverseLightSourceInObjectTree(GameObject* go)
{
	if (go->IsLightSource())
	{
		for (int i = 0; i < LIGHT_SOURCES_NUM; i++)
		{
			if (LightSourcesArray[i] == nullptr)
			{
				LightSourcesArray[i] = go;
				go->GetLightSourceData()->light_source_number = i;
				break;
			}
		}
		if (go->GetLightSourceData()->light_source_number <0 || go->GetLightSourceData()->light_source_number >LIGHT_SOURCES_NUM)
		{
			go->GetLightSourceData()->light_source_number = -1;
		}
	}
	for (int i = 0; i < go->getChildren().size(); i++)
	{
		GameObject* child = go->getChildren().at(i);
		TraverseLightSourceInObjectTree(child);
	}


}

Scene::Scene()
{
	SceneTimer = AnimationTimer();
	SceneTimer.StartTimer();
	SceneTimer.SampleNow();
	this->SceneInputSystem = new GOInputSystem();
	this->SceneMasterParent = new GameObject(nullptr, "scene_master", nullptr);
}

Scene::~Scene()
{
	if (SceneMasterParent != nullptr)
	{
		SceneMasterParent->Destroy(true);
	}
}

void Scene::StartScene()
{
	SetupScriptsForGameObjectHead(this, SceneMasterParent);
}

void Scene::RunSceneScripts()
{
	RunScripts(SceneMasterParent);
}

void Scene::DrawScene()
{
	RunGameObjectsForFrame(SceneMasterParent);
}


void RunScripts(GameObject* GOHead)
{
	if (GOHead == nullptr)
		return;

	//get and run script of game object
	GOScript* curr_script = GOHead->GetRunningScript();
	if (curr_script != nullptr)
	{
		curr_script->SLoop();
	}

	//run scripts for children
	auto children = GOHead->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		GameObject* curr_child = children.at(i);
		RunScripts(curr_child);
	}
}

//apply transforms, and drawables for all objects in the scene
void RunGameObjectsForFrame(GameObject* GOHead)
{
	GOTransform* _obj_trans = nullptr;
	GODrawable* _obj_Draw = nullptr;

	if (GOHead == nullptr)
		return;

	_obj_Draw = GOHead->GetDrawableObject();

	//set transform
	if (GOHead->GetTransform() != nullptr) {

		_obj_trans = GOHead->GetTransform();
		_obj_trans->PushObjectTransformMatrix();
	}

	//draw object
	if (_obj_Draw != nullptr)
	{
		_obj_Draw->SetActiveMat();
		_obj_Draw->DrawObject();
	}

	//run for children game objects
	auto children = GOHead->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		GameObject* curr_child = children.at(i);
		RunGameObjectsForFrame(curr_child);
	}

	//undo transform
	if (_obj_trans != nullptr)
		_obj_trans->PopObjectTransformMatrix();
}

void SetupScriptsForGameObjectHead(Scene* CurrScene, GameObject* GOHead)
{
	if (GOHead == nullptr)
		return;

	//get and run script of game object
	GOScript* curr_script = GOHead->GetRunningScript();
	if (curr_script != nullptr)
	{
		curr_script->SetupOnce(CurrScene);
	}

	//run scripts for children
	auto children = GOHead->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		GameObject* curr_child = children.at(i);
		SetupScriptsForGameObjectHead(CurrScene, curr_child);
	}
}

/// <summary>
/// calculates the world position for GameObject relative to the parents
/// </summary>
/// <param name="SpecialObject"></param>
void CaculateWorldPosition(GameObject* GO_in)
{
	// Set this to the identity matrix
	glm::mat4 ResultMatrixTransformation = glm::mat4(1.0f);

	GameObject* obj = GO_in;
	while (obj->GetParent() != nullptr)
	{
		obj = obj->GetParent();

		// Get the scale, rotation, and position of the current GameObject
		if (obj->GetTransform() != nullptr)
		{
			GOTransform* tempTransform = obj->GetTransform();
			GOvec3 objScale = tempTransform->GetScale();
			GOvec3 objPosition = tempTransform->GetPosition();
			GOvec3 objRotation = tempTransform->GetRotation();

			glm::vec3 scale = glm::vec3(objScale.x, objScale.y, objScale.z);
			glm::vec3 position = glm::vec3(objPosition.x, objPosition.y, objPosition.z);
			glm::vec3 rotation = glm::vec3(objRotation.x, objRotation.y, objRotation.z);

			// Create transformation matrices
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
			glm::mat4 rotateXMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotateYMatrix = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotateZMatrix = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), position);

			// Combine the transformations in the correct order: scale, rotate, then translate
			glm::mat4 transformMatrix = translateMatrix * rotateZMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

			// Multiply with the ResultMatrixTransformation and store in ResultMatrixTransformation
			ResultMatrixTransformation = transformMatrix * ResultMatrixTransformation;
		}
		if (GO_in->GetTransform() != nullptr)
		{
			//finally calculate and update the world position
			GOTransform* tempTransform = GO_in->GetTransform();
			GOvec3 objPosition = tempTransform->GetPosition();
			glm::vec3 position = glm::vec3(objPosition.x, objPosition.y, objPosition.z);
			// Convert the local position to a 4D homogeneous coordinate
			glm::vec4 localPosition4D = glm::vec4(position, 1.0f);

			glm::vec3 claculated_position = ResultMatrixTransformation * localPosition4D;
			tempTransform->setPosition(claculated_position.x, claculated_position.y, claculated_position.z);
		}
	}

	// Use the ResultMatrixTransformation as needed, e.g., setting it to the SpecialObject's world transformation
}

/// <summary>
/// returns a vector full of found gameobjects that are not regular
/// </summary>
/// <returns></returns>
std::vector<GameObject*> Scene::GetSpecialGameObjects()
{
	std::vector<GameObject*> ret_vec = std::vector<GameObject*>();


	GetAllSpecialObjectsForObjTree(this->SceneMasterParent, &ret_vec);

	//after got all special objects, get them to calculate position
	for (int i = 0; i < ret_vec.size(); i++)
	{
		ret_vec.at(i)->CalculateWorldPosition();
	}

	return ret_vec;
}

/// <summary>
/// recursive function that iterates over GOObject trees and find special objects and push them to the GOMem vector
/// </summary>
/// <param name="head">the haed GameObject</param>
/// <param name="GOMem">holds all result objects</param>
void GetAllSpecialObjectsForObjTree(GameObject* head, std::vector<GameObject*>* GOMem)
{
	if (head->GetGoType() != regular)
	{
		GOMem->push_back(head);
	}
	auto children = head->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		GetAllSpecialObjectsForObjTree(children.at(i), GOMem);
	}
}



GameObject* SearchObjectByNameInObjectTree(std::string objName, GameObject* objTree)
{
	GameObject* res_obj = nullptr;
	if (objTree == nullptr)
		return res_obj;

	if (objTree->GetName() == objName)//test head
	{
		res_obj = objTree;
		return res_obj;
	}
	auto obj_children = objTree->getChildren();
	if (obj_children.size() <= 0)
		return res_obj;

	for (int i = 0; i < obj_children.size(); i++)
	{
		GameObject* curr_child = obj_children.at(i);
		auto child_res = SearchObjectByNameInObjectTree(objName, curr_child);//search in child tree for res object
		if (child_res != nullptr)
		{
			res_obj = child_res;
			return res_obj;
		}
	}
	return res_obj;
}