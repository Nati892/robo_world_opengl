#pragma once
#include "stdafx.h"
#include "GOScript.h"
#include "AnimationTimer.h"
#include "GameObject.h"
#include "GOTransform.h"
#include "GODrawable.h"
//write game script headers here

class GOInputSystem;
class DynamicSurfaceScript;

enum axis
{
	axis_x,
	axis_y,
	axis_z,
};
class BasicAxisRotateScript :public GOScript
{
private:
	AnimationTimer* rotate_timer;
	AnimationTimer* color_timer;
	float speed = 1;
	axis _rotation_axis = axis_x;
	//virtual inherited
	void SSetup(Scene* CurrScene);
public:
	//virtual inherited
	void SLoop();
	void SCleanUp();
	void SetSpeed(float speed);
	void SetRotationAxis(axis a);
};

enum cam_mode
{
	cam_mode_fps,
	cam_mode_tps,
};

class CameraControllerScript :public GOScript
{
private:
	Scene* this_scene;
	GOInputSystem* this_input_sys;
	GameObject* CamObject;
	GameObject* LookAtObject;
	GameObject* DynamicSurface;
	GameObject* FollowObject;
	GOTransform* FollowObjectTrans;
	GameObject* CamHeadObject;
	GameObject* RobotHeadObject;
	GOTransform* HeadObjectTrans;
	GOTransform* LookAtObjectTrans;
	GOTransform* CamObjectTrans;
	GameObject* PlayerHolderObject;
	GOTransform* MoveObjectTrans;
	DynamicSurfaceScript* CurrDynamicSurfaceScript;

	//cam head transform modes
	GOTransform FirstPersonCamHeadTransfrom;
	GOTransform ThirdPersonCamHeadTransfrom;
	GOTransform FreeRoamCamHeadTransfrom;

	//cam lookat transform modes
	GOTransform ThirdPersonLookAtTransfrom;
	GOTransform FreeRoamLookAtTransfrom;
	GOTransform FirstPersonLookAtTransfrom;

	//cam transfrom modes
	GOTransform ThirdPersonCamTransfrom;
	GOTransform FreeRoamCamTransfrom;
	GOTransform FirstPersonCamTransfrom;

	float y_axis_limit = 50.0f;
	float speed;
	bool ThirdPersonCamera = true;// input #1
	bool lock_mouse = false;
	cam_mode curr_cam_mode = cam_mode_tps;

	void SSetup(Scene* CurrScene);

public:
	//virtual inherited
	void SLoop();
	void SCleanUp();
};



class DynamicSurfaceScript :public GOScript
{
private:

	glm::vec3 _Scale;
	glm::vec3 _Count;
	glm::vec3 _Position;
	bool is_textured;

	void SSetup(Scene* CurrScene);
public:
	//virtual inherited
	DynamicSurfaceScript(glm::vec3 _Scale, glm::vec3 _Count, bool is_textured = true);
	void SLoop();
	void UpdatePosition(glm::vec3 new_pos);
	void SCleanUp();

};


class SkyBoxScript :public GOScript
{
private:
	std::string FollowObjName;
	GameObject* FollowObject;
	GOTransform* FollowObjectTransform;

	void SSetup(Scene* CurrScene);
public:
	//virtual inherited
	SkyBoxScript(std::string follow_object_name);
	void SLoop();
	void SCleanUp();

};