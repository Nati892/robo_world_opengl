#include "GameScripts.h"
#include "Scene.h"
#include "GOInputSystem.h"
void BasicAxisRotateScript::SSetup(Scene* CurrScene)
{
	rotate_timer = new AnimationTimer(10, 0, 360);
	color_timer = new AnimationTimer(5, 1, 255);
	rotate_timer->StartTimer();
	color_timer->StartTimer();
	GameObject* my_go = this->GetGameObject();
	if (my_go->GetName() == "child2")
	{
		my_go->SetGOType(GOCamLookAtPoint);
	}
}

void BasicAxisRotateScript::SLoop()
{
	auto val = rotate_timer->GetCurrentAnimationValue();
	auto val2 = color_timer->GetCurrentAnimationValue();
	GameObject* my_go = this->GetGameObject();
	GODrawable* my_draw = my_go->GetDrawableObject();
	GOTransform* my_trans = my_go->GetTransform();
	if (my_draw != nullptr)
	{
		float curr_new_red_val = (((float)val2) / (255.0f));
		auto curr_diff = my_draw->getDiffuseColor();
		auto curr_ambiant = my_draw->getAmbientColor();
		my_draw->setDiffuseColor(curr_new_red_val, 0, 0, curr_diff.z);
	}

	if (my_trans != nullptr)
	{
		auto curr_rot = my_trans->GetRotation();
		switch (_rotation_axis)
		{
		case axis_x:
			my_trans->setRotation(val, curr_rot.y, curr_rot.z);
			break;
		case axis_y:
			my_trans->setRotation(curr_rot.x, val, curr_rot.z);
			break;
		case axis_z:
			my_trans->setRotation(curr_rot.x, curr_rot.y, val);
			break;
		default:
			_rotation_axis = axis_x;
			break;
		}
	}
}

void BasicAxisRotateScript::SCleanUp()
{
	delete this->rotate_timer;
	delete this->color_timer;
}

void BasicAxisRotateScript::SetSpeed(float speed)
{
	if (this->rotate_timer != nullptr)
		this->rotate_timer->SetSpeed(speed);
}

void BasicAxisRotateScript::SetRotationAxis(axis a)
{
	switch (a)
	{
	case axis_x:
		this->_rotation_axis = axis_x;
		break;
	case axis_y:
		this->_rotation_axis = axis_y;
		break;
	case axis_z:
		this->_rotation_axis = axis_z;
		break;
	default:
		this->_rotation_axis = axis_x;
		break;
	}
}

glm::quat EulerToQuaternion(glm::vec3 euler) {
	return glm::quat(glm::vec3(glm::radians(euler.x), glm::radians(euler.y), glm::radians(euler.z)));
}

glm::vec3 QuaternionToEuler(glm::quat quat) {
	glm::vec3 euler = glm::eulerAngles(quat);
	return glm::vec3(glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z));
}

void CameraControllerScript::SSetup(Scene* CurrScene)
{
	this->this_scene = CurrScene;
	if (this->this_scene != nullptr)
	{
		this->this_input_sys = this->this_scene->GetSceneInputSystem();
		this->CamObject = this_scene->FindObjectByName("MainCam");
		this->LookAtObject = this_scene->FindObjectByName("MainCamLookAt");
		this->DynamicSurface = this_scene->FindObjectByName("dynamic_surface2d");
		this->FollowObject = this_scene->FindObjectByName("player");
		this->PlayerHolderObject = this_scene->FindObjectByName("player_holder");
		this->CamHeadObject = this_scene->FindObjectByName("CamHead");
		this->RobotHeadObject = this_scene->FindObjectByName("player_head");
	}
	if (DynamicSurface != nullptr)
	{
		CurrDynamicSurfaceScript = dynamic_cast<DynamicSurfaceScript*>(DynamicSurface->GetRunningScript());
	}
	if (FollowObject != nullptr)
	{
		FollowObjectTrans = FollowObject->GetTransform();
	}
	if (PlayerHolderObject != nullptr)
	{
		MoveObjectTrans = PlayerHolderObject->GetTransform();
	}
	if (CamObject != nullptr)
	{
		CamObjectTrans = CamObject->GetTransform();
	}
	if (CamHeadObject != nullptr)
	{
		HeadObjectTrans = CamHeadObject->GetTransform();
	}
	if (LookAtObject != nullptr)
	{
		LookAtObjectTrans = LookAtObject->GetTransform();
	}

	//fps
	this->FirstPersonCamHeadTransfrom.setPosition(2, 0, 0);
	this->FirstPersonCamHeadTransfrom.setRotation(0, 0, 0);
	this->FirstPersonCamHeadTransfrom.setScale(1, 1, 1);

	this->FirstPersonLookAtTransfrom.setPosition(3, 0, 0);
	this->FirstPersonLookAtTransfrom.setRotation(0, 0, 0);
	this->FirstPersonLookAtTransfrom.setScale(1, 1, 1);

	this->FirstPersonCamTransfrom.setPosition(0, 0, 0);
	this->FirstPersonCamTransfrom.setRotation(0, 0, 0);
	this->FirstPersonCamTransfrom.setScale(1, 1, 1);

	//3ps
	this->ThirdPersonCamHeadTransfrom.setPosition(0, 0, 0);
	this->ThirdPersonCamHeadTransfrom.setRotation(0, 0, 0);
	this->ThirdPersonCamHeadTransfrom.setScale(1, 1, 1);

	this->ThirdPersonLookAtTransfrom.setPosition(0, 0, 0);
	this->ThirdPersonLookAtTransfrom.setRotation(0, 0, 0);
	this->ThirdPersonLookAtTransfrom.setScale(1, 1, 1);

	this->ThirdPersonCamTransfrom.setPosition(-3, 0, 0);
	this->ThirdPersonCamTransfrom.setRotation(0, 0, 0);
	this->ThirdPersonCamTransfrom.setScale(1, 1, 1);

	//free roam
	this->FreeRoamCamHeadTransfrom.setPosition(3, 3, 3);
	this->FreeRoamCamHeadTransfrom.setRotation(0, 0, 0);
	this->FreeRoamCamHeadTransfrom.setScale(1, 1, 1);

	this->FreeRoamLookAtTransfrom.setPosition(1, 0, 0);
	this->FreeRoamLookAtTransfrom.setRotation(0, 0, 0);
	this->FreeRoamLookAtTransfrom.setScale(1, 1, 1);

	this->FreeRoamCamTransfrom.setPosition(0, 0, 0);
	this->FreeRoamCamTransfrom.setRotation(0, 0, 0);
	this->FreeRoamCamTransfrom.setScale(1, 1, 1);

	this->RobotHeadObject->AddChildObject(CamHeadObject);//make camera child of robot
	HeadObjectTrans->setValues(&(this->ThirdPersonCamHeadTransfrom));//add the deafult transform

}

void CameraControllerScript::SLoop()
{
	GameObject* my_go = this->GetGameObject();
	GOTransform* my_trans = my_go->GetTransform();

	if (this_input_sys == nullptr)
		return;

	if (this_input_sys->IsKeyPressed('q') || this_input_sys->IsKeyPressed('Q'))
	{
		exit(0);
	}
	if (this_input_sys->IsKeyPressed('v') || this_input_sys->IsKeyPressed('v'))//if press v many times, scene goes wonky, todo FIX this!
	{
		switch (this->curr_cam_mode)
		{
		case cam_mode_fps:
			this->curr_cam_mode = cam_mode_tps;
			this->RobotHeadObject->AddChildObject(this->CamHeadObject);
			HeadObjectTrans->setValues(&(this->ThirdPersonCamHeadTransfrom));
			CamObjectTrans->setValues(&(this->ThirdPersonCamTransfrom));
			LookAtObjectTrans->setValues(&(this->ThirdPersonLookAtTransfrom));
			break;
		case cam_mode_tps:
			this->curr_cam_mode = cam_mode_free_mode;
			this->this_scene->AddGameObjectTree(this->CamHeadObject);
			HeadObjectTrans->setValues(&(this->FreeRoamCamHeadTransfrom));
			CamObjectTrans->setValues(&(this->FreeRoamCamTransfrom));
			LookAtObjectTrans->setValues(&(this->FreeRoamLookAtTransfrom));
			break;
		case cam_mode_free_mode:
			this->curr_cam_mode = cam_mode_fps;
			this->RobotHeadObject->AddChildObject(this->CamHeadObject);
			HeadObjectTrans->setValues(&(this->FirstPersonCamHeadTransfrom));
			CamObjectTrans->setValues(&(this->ThirdPersonCamTransfrom));
			LookAtObjectTrans->setValues(&(this->FirstPersonLookAtTransfrom));
			break;
		default:
			this->curr_cam_mode = cam_mode_free_mode;
			this->this_scene->AddGameObjectTree(this->CamHeadObject);
			CamObjectTrans->setValues(&(this->FreeRoamCamTransfrom));
			HeadObjectTrans->setValues(&(this->FreeRoamCamHeadTransfrom));
			LookAtObjectTrans->setValues(&(this->FreeRoamLookAtTransfrom));
			break;
		}
	}


	int x_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::X_AXIS);
	int y_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::Y_AXIS);
	glm::vec3 total_movement;
	glm::vec3 movement_vec;

	switch (this->curr_cam_mode)
	{
	case cam_mode_fps:
		break;

	case cam_mode_tps:
		if (x_movement != 0 || y_movement != 0) {
			// Get current rotation in Euler angles
			glm::vec3 currentEulerRotation = HeadObjectTrans->GetRotation();

			// Convert current Euler angles to quaternion
			glm::quat currentQuat = EulerToQuaternion(currentEulerRotation);

			// Calculate the quaternion representing the mouse movement
			glm::quat xQuat = glm::angleAxis(glm::radians(static_cast<float>(x_movement * -1)), glm::vec3(0, 1, 0));
			glm::quat yQuat = glm::angleAxis(glm::radians(static_cast<float>(y_movement * -1)), glm::vec3(1, 0, 0));

			// Apply the rotations
			glm::quat newQuat = xQuat * currentQuat * yQuat;

			// Convert the resulting quaternion back to Euler angles
			glm::vec3 newEulerRotation = QuaternionToEuler(newQuat);

			// Set the new rotation
			HeadObjectTrans->setRotation(newEulerRotation);
		}
		break;


	case cam_mode_free_mode:
		glm::vec3 movement = this->LookAtObject->GetCalculatedLocation() - this->CamObject->GetCalculatedLocation();
		auto res = glm::normalize(movement);
		movement = glm::vec3{ res.x,res.y,res.z };
		movement *= 0.2f;
		if (this_input_sys->IsKeyPressed('w') || this_input_sys->IsKeyPressed('W'))
		{
			this->HeadObjectTrans->setPosition(this->HeadObjectTrans->GetPosition() + movement);
		}
		if (this_input_sys->IsKeyPressed('s') || this_input_sys->IsKeyPressed('S'))
		{
			movement *= -1;
			this->HeadObjectTrans->setPosition(this->HeadObjectTrans->GetPosition() + movement);
		}
		if (this_input_sys->IsKeyPressed('a') || this_input_sys->IsKeyPressed('A'))
		{

			this->HeadObjectTrans->setPosition(this->HeadObjectTrans->GetPosition() + movement);
		}
		if (this_input_sys->IsKeyPressed('d') || this_input_sys->IsKeyPressed('D'))
		{
			this->HeadObjectTrans->setPosition(this->HeadObjectTrans->GetPosition() + movement);
		}

		movement_vec = glm::vec3{ 0,0,0 };
		if (x_movement != 0)
		{
			movement_vec += glm::vec3{ 0,static_cast<float>(x_movement * -1),0 };
		}
		if (y_movement != 0)
		{
			movement_vec += glm::vec3{ static_cast<float>(y_movement * -1),0,0 };
		}
		// Scale the movement vector by the delta time
		if (y_movement != 0 || x_movement != 0)
		{
			movement_vec *= this->this_scene->GetDeltaTime();

			//// Get the current rotation in Euler angles (assuming in degrees)
			glm::vec3 current_rotation_euler = this->HeadObjectTrans->GetRotation();
			//glm::vec3 current_rotation_euler_glm = glm::vec3(current_rotation_euler.x, current_rotation_euler.y, current_rotation_euler.z);

			//// Convert current Euler angles to radians
			//glm::vec3 current_rotation_radians = glm::radians(current_rotation_euler_glm);

			//// Create rotation matrices for the pitch and yaw rotations
			//glm::mat4 yaw_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(movement_vec.x), glm::vec3(1.0f, 0.0f, 0.0f));
			//glm::mat4 pitch_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(movement_vec.y), glm::vec3(0.0f, 1.0f, 0.0f));

			//// Create a rotation matrix from the current rotation
			//glm::mat4 current_rotation_matrix = glm::eulerAngleXYZ(current_rotation_radians.x, current_rotation_radians.y, current_rotation_radians.z);

			//// Apply the new pitch and yaw rotations to the current rotation matrix
			//glm::mat4 new_rotation_matrix = current_rotation_matrix*(yaw_matrix * pitch_matrix) ;

			//// Extract the new rotation as a quaternion
			//glm::quat new_rotation_quat = glm::quat_cast(new_rotation_matrix);

			//// Extract the new Euler angles from the quaternion
			//glm::vec3 new_rotation_euler = glm::degrees(glm::eulerAngles(new_rotation_quat));

			//// Set the new rotation
			//this->HeadObjectTrans->setRotation(glm::vec3{ new_rotation_euler.x, new_rotation_euler.y, new_rotation_euler.z });


		}
		break;
	}

	////check foword motion 'w' key



	//	CurrDynamicSurfaceScript->UpdatePosition(MoveObjectTrans->GetPosition());

	//	auto rot = FollowObjectTrans->GetRotation();
	//	rot.y = my_trans->GetRotation().y;
	//	FollowObjectTrans->setRotation(rot + glm::vec3{ 0,90,0 });
	//}

	//int x_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::X_AXIS);
	//int y_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::Y_AXIS);
	//auto movement_vec = glm::vec3{ 0,0,0 };
	//if (x_movement != 0)
	//{
	//	movement_vec += glm::vec3{ 0,static_cast<float>(x_movement * -1),0 };
	//}
	//if (y_movement != 0)
	//{
	//	movement_vec += glm::vec3{ static_cast<float>(y_movement * -1),0,0 };
	//}

	//movement_vec *= this->this_scene->GetDeltaTime();

	//auto total_movement = my_trans->GetRotation() + movement_vec;

	////cutoff
	//if (total_movement.x < -30)
	//{
	//	total_movement.x = -30;
	//}
	//if (total_movement.x > 60)
	//{
	//	total_movement.x = 60;
	//}

	//my_trans->setRotation(total_movement);

	//if (!this->ThirdPersonCamera) {
	//	auto rot = FollowObjectTrans->GetRotation();
	//	rot.y = my_trans->GetRotation().y;
	//	FollowObjectTrans->setRotation(rot + glm::vec3{ 0,90,0 });
	//}

}

void CameraControllerScript::SCleanUp()
{
}

void DynamicSurfaceScript::SSetup(Scene* CurrScene)
{
	if (is_textured) {
		for (int i = -_Count.x / 2; i < _Count.x / 2; i++)
		{
			for (int j = -_Count.z / 2; j < _Count.z / 2; j++)
			{
				auto new_surface = Prefabs::GetReadySurface2d("surface" + i + j, "surface_board_texture.jpg");
				if (new_surface != nullptr && new_surface->GetTransform() != nullptr)
				{
					// Calculate new position
					auto new_pos = glm::vec3{ ((float)i) * _Scale.x, 0 ,((float)j) * _Scale.z };
					new_surface->GetTransform()->setPosition(new_pos);

					// Set the scale of the tile
					new_surface->GetTransform()->setScale(glm::vec3{ _Scale.x, 1 ,_Scale.z });

					// Add to scene tree
					this->GetGameObject()->AddChildObject(new_surface);
				}

			}
		}
	}
	else
	{
		for (int i = -_Count.x / 2; i < _Count.x / 2; i++)
		{
			for (int j = -_Count.z / 2; j < _Count.z / 2; j++)
			{
				auto new_surface = Prefabs::GetReadyCheckboardSurface2d("surface" + i + j);
				if (new_surface != nullptr && new_surface->GetTransform() != nullptr)
				{
					// Calculate new position
					auto new_pos = glm::vec3{ ((float)i) * _Scale.x, 0 ,((float)j) * _Scale.z };
					new_surface->GetTransform()->setPosition(new_pos);

					// Set the scale of the tile
					new_surface->GetTransform()->setScale(glm::vec3{ _Scale.x, 1 ,_Scale.z });

					// Add to scene tree
					this->GetGameObject()->AddChildObject(new_surface);
				}

			}
		}
	}
}


DynamicSurfaceScript::DynamicSurfaceScript(glm::vec3 Scale, glm::vec3 Count, bool is_textured)
{
	this->is_textured = is_textured;
	this->_Scale = Scale;
	this->_Count = Count;
}

int adjustToScale(int number, int scale)
{
	if (scale == 0) return number; // Avoid division by zero

	// Calculate remainder and adjust number
	int remainder = number % scale;

	// If the number is negative and has a remainder, adjust the number down further
	if (number < 0 && remainder != 0)
		return number - remainder - scale;

	return number - remainder;
}

void DynamicSurfaceScript::SLoop()
{
	glm::vec3 res = { adjustToScale(_Position.x,_Scale.x),0,adjustToScale(_Position.z,_Scale.z) };
	this->GetGameObject()->GetTransform()->setPosition(res);
}


void DynamicSurfaceScript::UpdatePosition(glm::vec3 new_pos)
{
	this->_Position = new_pos;
}

void DynamicSurfaceScript::SCleanUp()
{
}


/// SkyBox script///


void SkyBoxScript::SSetup(Scene* CurrScene)
{
	GameObject* go = CurrScene->FindObjectByName(this->FollowObjName);
	if (go != nullptr)
	{
		this->FollowObject = go;
		auto trans = go->GetTransform();
		if (trans != nullptr)
		{
			this->FollowObjectTransform = trans;
		}
	}
}

SkyBoxScript::SkyBoxScript(std::string follow_object_name)
{
	this->FollowObjName = follow_object_name;
}

void SkyBoxScript::SLoop()
{

	if (this->FollowObjectTransform != nullptr)
	{
		auto pos = FollowObjectTransform->GetPosition();
		this->GetGameObject()->GetTransform()->setPosition(pos + glm::vec3{ 0,-45,0 });

	}
}

void SkyBoxScript::SCleanUp()
{
}
