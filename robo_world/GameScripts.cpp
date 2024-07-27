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
		my_go->SetGOType(GOCamLookAt);
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

void Camera3rdPerson::SSetup(Scene* CurrScene)
{
	this->this_scene = CurrScene;
	if (this->this_scene != nullptr)
	{
		this->this_input_sys = this->this_scene->GetSceneInputSystem();
		this->CamObject = this_scene->FindObjectByName("MainCam");
		this->LookAtObject = this_scene->FindObjectByName("MainCamLookAt");
		this->DynamicSurface = this_scene->FindObjectByName("dynamic_surface2d");
		this->FollowObject = this_scene->FindObjectByName("player");
		this->MoveObject = this_scene->FindObjectByName("player_holder");
		this->CamHeadObject = this_scene->FindObjectByName("CamHead");
		this->RobotHeadObject = this_scene->FindObjectByName("robot_head");
	}
	if (DynamicSurface != nullptr)
	{
		CurrDynamicSurfaceScript = dynamic_cast<DynamicSurfaceScript*>(DynamicSurface->GetRunningScript());
	}
	if (FollowObject != nullptr)
	{
		FollowObjectTrans = FollowObject->GetTransform();
	}
	if (MoveObject != nullptr)
	{
		MoveObjectTrans = MoveObject->GetTransform();
	}
	if (CamHeadObject != nullptr)
	{
		HeadObjectTrans = CamHeadObject->GetTransform();
	}
}

void Camera3rdPerson::SLoop()
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
		this->ThirdPersonCamera = !this->ThirdPersonCamera;
		if (this->ThirdPersonCamera)
		{
			HeadObjectTrans->setPosition(0, 0, 0);
			CamObject->GetTransform()->setPosition(0, 7, 3);
			LookAtObject->GetTransform()->setPosition(0, 2, 0);
		}
		else
		{
			HeadObjectTrans->setPosition(0, -1, 0);
			CamObject->GetTransform()->setPosition(0, 4, -3);
			LookAtObject->GetTransform()->setPosition(0, 4, -6);
		}
	}
	//check foword motion 'w' key
	if (this_input_sys->IsKeyPressed('w') || this_input_sys->IsKeyPressed('W'))
	{
		GOvec3 movement = this->LookAtObject->GetCalculatedLocation() - this->CamObject->GetCalculatedLocation();
		auto res = glm::normalize(glm::vec3(movement.x, movement.y, movement.z));
		movement = GOvec3{ res.x,res.y,res.z };
		movement.y = 0;
		movement *= 0.2f;
		MoveObjectTrans->setPosition(MoveObjectTrans->GetPosition() + movement);
		CurrDynamicSurfaceScript->UpdatePosition(MoveObjectTrans->GetPosition());

		auto rot = FollowObjectTrans->GetRotation();
		rot.y = my_trans->GetRotation().y;
		FollowObjectTrans->setRotation(rot + GOvec3{ 0,90,0 });
	}

	int x_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::X_AXIS);
	int y_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::Y_AXIS);
	auto movement_vec = GOvec3{ 0,0,0 };
	if (x_movement != 0)
	{
		movement_vec += GOvec3{ 0,static_cast<float>(x_movement * -1),0 };
	}
	if (y_movement != 0)
	{
		movement_vec += GOvec3{ static_cast<float>(y_movement * -1),0,0 };
	}

	movement_vec *= this->this_scene->GetDeltaTime();

	auto total_movement = my_trans->GetRotation() + movement_vec;

	//cutoff
	if (total_movement.x < -30)
	{
		total_movement.x = -30;
	}
	if (total_movement.x > 60)
	{
		total_movement.x = 60;
	}

	my_trans->setRotation(total_movement);

	if (!this->ThirdPersonCamera) {
		auto rot = FollowObjectTrans->GetRotation();
		rot.y = my_trans->GetRotation().y;
		FollowObjectTrans->setRotation(rot + GOvec3{ 0,90,0 });
	}

}

void Camera3rdPerson::SCleanUp()
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
					auto new_pos = GOvec3{ ((float)i) * _Scale.x, 0 ,((float)j) * _Scale.z };
					new_surface->GetTransform()->setPosition(new_pos);

					// Set the scale of the tile
					new_surface->GetTransform()->setScale(GOvec3{ _Scale.x, 1 ,_Scale.z });

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
					auto new_pos = GOvec3{ ((float)i) * _Scale.x, 0 ,((float)j) * _Scale.z };
					new_surface->GetTransform()->setPosition(new_pos);

					// Set the scale of the tile
					new_surface->GetTransform()->setScale(GOvec3{ _Scale.x, 1 ,_Scale.z });

					// Add to scene tree
					this->GetGameObject()->AddChildObject(new_surface);
				}

			}
		}
	}
}


DynamicSurfaceScript::DynamicSurfaceScript(GOvec3 Scale, GOvec3 Count, bool is_textured)
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
	GOvec3 res = { adjustToScale(_Position.x,_Scale.x),0,adjustToScale(_Position.z,_Scale.z) };
	this->GetGameObject()->GetTransform()->setPosition(res);
}


void DynamicSurfaceScript::UpdatePosition(GOvec3 new_pos)
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
		this->GetGameObject()->GetTransform()->setPosition(pos + GOvec3{ 0,-45,0 });

	}
}

void SkyBoxScript::SCleanUp()
{
}
