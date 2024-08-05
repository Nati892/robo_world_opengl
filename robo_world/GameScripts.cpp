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
		this->PlayerObject = this_scene->FindObjectByName("player");
		this->PlayerHolderObject = this_scene->FindObjectByName("player_holder");
		this->CamHeadObject = this_scene->FindObjectByName("CamHead");
		this->RobotHeadObject = this_scene->FindObjectByName("player_head");

		this->MoveVecStart = this_scene->FindObjectByName("MoveVecStart");
		this->MoveVecEnd = this_scene->FindObjectByName("MoveVecEnd");
	}
	if (DynamicSurface != nullptr)
	{
		CurrDynamicSurfaceScript = dynamic_cast<DynamicSurfaceScript*>(DynamicSurface->GetRunningScript());
	}
	if (PlayerObject != nullptr)
	{
		PlayerObjectTrans = PlayerObject->GetTransform();
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
		CamHeadObjectTrans = CamHeadObject->GetTransform();
	}
	if (LookAtObject != nullptr)
	{
		LookAtObjectTrans = LookAtObject->GetTransform();
	}
	if (this->MoveVecStart != nullptr)
	{
		MoveVecStartTrans = MoveVecStart->GetTransform();
	}
	if (this->MoveVecEnd != nullptr)
	{
		MoveVecEndTrans = MoveVecEnd->GetTransform();
	}

	//fps
	this->FirstPersonCamHeadTransfrom.setPosition(-1, 0, 0);
	this->FirstPersonCamHeadTransfrom.setRotation(0, 0, 0);
	this->FirstPersonCamHeadTransfrom.setScale(1, 1, 1);

	this->FirstPersonLookAtTransfrom.setPosition(-1, 0, 0);
	this->FirstPersonLookAtTransfrom.setRotation(0, 0, 0);
	this->FirstPersonLookAtTransfrom.setScale(1, 1, 1);

	this->FirstPersonCamTransfrom.setPosition(0, 0, 0);
	this->FirstPersonCamTransfrom.setRotation(0, 0, 0);
	this->FirstPersonCamTransfrom.setScale(1, 1, 1);

	////tps mock
	this->ThirdPersonCamHeadTransfrom.setPosition(0, 0, 0);
	this->ThirdPersonCamHeadTransfrom.setRotation(0, 0, 0);
	this->ThirdPersonCamHeadTransfrom.setScale(1, 1, 1);

	this->ThirdPersonLookAtTransfrom.setPosition(0, 0, 0);
	this->ThirdPersonLookAtTransfrom.setRotation(0, 0, 0);
	this->ThirdPersonLookAtTransfrom.setScale(1, 1, 1);

	this->ThirdPersonCamTransfrom.setPosition(2, 2, 0);
	this->ThirdPersonCamTransfrom.setRotation(0, 0, 0);
	this->ThirdPersonCamTransfrom.setScale(1, 1, 1);

	this->curr_cam_mode = cam_mode_tps;
	this->RobotHeadObject->AddChildObject(this->CamHeadObject);
	CamHeadObjectTrans->setValues(&(this->ThirdPersonCamHeadTransfrom));
	CamObjectTrans->setValues(&(this->ThirdPersonCamTransfrom));
	LookAtObjectTrans->setValues(&(this->ThirdPersonLookAtTransfrom));
	this->speed = 5;
	this->rotation_speed = 15;
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
	if (this_input_sys->IsKeyPressed('v') || this_input_sys->IsKeyPressed('v'))
	{
		switch (this->curr_cam_mode)
		{
		case cam_mode_fps:
			this->curr_cam_mode = cam_mode_tps;
			this->PlayerHolderObject->AddChildObject(this->CamHeadObject);
			CamHeadObjectTrans->setValues(&(this->ThirdPersonCamHeadTransfrom));
			CamObjectTrans->setValues(&(this->ThirdPersonCamTransfrom));
			LookAtObjectTrans->setValues(&(this->ThirdPersonLookAtTransfrom));
			break;
		case cam_mode_tps:
			this->curr_cam_mode = cam_mode_fps;
			this->RobotHeadObject->AddChildObject(this->CamHeadObject);
			CamHeadObjectTrans->setValues(&(this->FirstPersonCamHeadTransfrom));
			CamObjectTrans->setValues(&(this->FirstPersonCamTransfrom));
			LookAtObjectTrans->setValues(&(this->FirstPersonLookAtTransfrom));
			break;

		}
	}

	int mouse_x_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::X_AXIS);
	int mouse_y_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::Y_AXIS);
	glm::vec3 total_movement;
	glm::vec3 movement_vec;
	auto step = MoveVecEnd->GetCalculatedLocation() - MoveVecStart->GetCalculatedLocation();

	step.y = 0;
	auto norm_step = glm::normalize(step);
	norm_step *= this_scene->GetDeltaTime();
	//general movement control

	if (this_input_sys->IsKeyPressed('w') || this_input_sys->IsKeyPressed('W'))
	{
		PlayerHolderObject->GetTransform()->setPosition(PlayerHolderObject->GetTransform()->GetPosition() + norm_step * speed);
		CurrDynamicSurfaceScript->UpdatePosition(PlayerHolderObject->GetTransform()->GetPosition());
	}
	if (this_input_sys->IsKeyPressed('s') || this_input_sys->IsKeyPressed('S'))
	{
		norm_step *= -1;
		PlayerHolderObject->GetTransform()->setPosition(PlayerHolderObject->GetTransform()->GetPosition() + norm_step * speed);
		CurrDynamicSurfaceScript->UpdatePosition(PlayerHolderObject->GetTransform()->GetPosition());
	}
	if (this_input_sys->IsKeyPressed('a') || this_input_sys->IsKeyPressed('A'))//left
	{
		MoveObjectTrans->setRotation(MoveObjectTrans->GetRotation() + glm::vec3(0, rotation_speed * this_scene->GetDeltaTime(), 0));
	}
	if (this_input_sys->IsKeyPressed('d') || this_input_sys->IsKeyPressed('D'))//right
	{
		MoveObjectTrans->setRotation(MoveObjectTrans->GetRotation() + glm::vec3(0, rotation_speed * this_scene->GetDeltaTime() * -1, 0));
	}


	switch (this->curr_cam_mode)
	{
	case cam_mode_fps:
		break;

	case cam_mode_tps:
		if (mouse_x_movement != 0)
		{
			auto new_rot = CamHeadObjectTrans->GetRotation();
			new_rot.y -= mouse_x_movement / 10.0f;
			this->CamHeadObjectTrans->setRotation(new_rot);
		}
		if (mouse_y_movement != 0)
		{
			auto old_pos = CamObjectTrans->GetPosition();
			auto new_pos = old_pos;
			new_pos.y += mouse_y_movement / 100.0f;
			if (new_pos.y < 1)
				new_pos.y = 1;

			if (new_pos.y > 4)
				new_pos.y = 4;

			//Pitmagoras for uniform distance from cam to robo body
			auto in_sqrt_res = 5 - powf(new_pos.y, 2);
			if (in_sqrt_res <= 0)
			{
				new_pos.x = 0.1;
				new_pos.y = old_pos.y;
			}
			else
			{
				new_pos.x = sqrtf(in_sqrt_res);
			}
			
			this->CamObjectTrans->setPosition(new_pos);
		}
		break;
	}

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
