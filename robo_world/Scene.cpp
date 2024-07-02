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

	auto HolderScript = new BasicCamHeadMove();
	CameraHolder->AttachScript(HolderScript);

	//test light source
	GameObject* LightsHolder = new GameObject(nullptr, "LightsHolder", nullptr);
	ret_scene->AddGameObjectTree(LightsHolder);

	GameObject* light0 = Prefabs::GetReadyLightSource();
	GameObject* light1 = Prefabs::GetReadyLightSource();
	GameObject* light2 = Prefabs::GetReadyLightSource();
	GameObject* light3 = Prefabs::GetReadyLightSource();

	LightsHolder->addChildObject(light0);
	LightsHolder->addChildObject(light1);
	LightsHolder->addChildObject(light2);
	LightsHolder->addChildObject(light3);

	auto l_trans = light0->GetTransform();
	l_trans->setPosition(-20, 0, 0);

	l_trans = light1->GetTransform();
	l_trans->setPosition(20, 0, 0);

	l_trans = light2->GetTransform();
	l_trans->setPosition(0, 20, 10);

	l_trans = light3->GetTransform();
	l_trans->setPosition(0, -20, 10);

	return ret_scene;
}

void Scene::AddGameObjectTree(GameObject* obj)
{
	if (obj != nullptr)
		this->SceneObjects.push_back(obj);
}

void Scene::TraverseLightSources()
{
	for (int i = 0; i < LIGHT_SOURCES_NUM; i++)
	{
		LightSourcesArray[i] = nullptr;
	}
	for (int i = 0; i < this->GetChildren().size(); i++)
	{
		auto curr_child = this->GetChildren().at(i);
		TraverseLightSourceInObjectTree(curr_child);
	}
}

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

void Scene::StartScene()
{
	GameObject* curr_GO;
	for (int i = 0; i < this->SceneObjects.size(); i++)
	{
		curr_GO = SceneObjects.at(i);
		SetupScriptsForGameObjectHead(curr_GO);
	}
}

void Scene::RunSceneScripts()
{

	GameObject* curr_GO;
	for (int i = 0; i < this->SceneObjects.size(); i++)
	{
		curr_GO = SceneObjects.at(i);
		RunScripts(curr_GO);
	}
}

void Scene::DrawScene()
{
	GameObject* curr_GO;
	for (int i = 0; i < this->SceneObjects.size(); i++)
	{
		curr_GO = SceneObjects.at(i);
		RunGameObjectsForFrame(curr_GO);
	}
}

std::vector<GameObject*> Scene::GetChildren()
{
	return this->SceneObjects;
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

	if (GOHead == nullptr || GOHead->GetDrawableObject() == nullptr)
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

void SetupScriptForGameObject(GameObject* GO_in)
{
	if (GO_in == nullptr)
		return;

	GOScript* GO_Script = GO_in->GetRunningScript();
	if (GO_Script != nullptr)
	{
		GO_Script->SetupOnce();
	}
}

void SetupScriptsForGameObjectHead(GameObject* GOHead)
{
	if (GOHead == nullptr)
		return;

	//get and run script of game object
	GOScript* curr_script = GOHead->GetRunningScript();
	if (curr_script != nullptr)
	{
		curr_script->SetupOnce();
	}

	//run scripts for children
	auto children = GOHead->getChildren();
	for (int i = 0; i < children.size(); i++)
	{
		GameObject* curr_child = children.at(i);
		SetupScriptsForGameObjectHead(curr_child);
	}
}

//another traversal func to get light distances where it goes for each light source up the parent tree and then calculates the trasforms


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

	for (int i = 0; i < this->GetChildren().size(); i++)
	{
		auto curr_child = this->GetChildren().at(i);
		GetAllSpecialObjectsForObjTree(curr_child, &ret_vec);
	}

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


