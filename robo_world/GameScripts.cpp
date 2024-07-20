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
	}
	if (DynamicSurface != nullptr)
	{

		CurrDynamicSurfaceScript =dynamic_cast<DynamicSurfaceScript*>(DynamicSurface->GetRunningScript());
	}
}

void Camera3rdPerson::SLoop()
{

	GameObject* my_go = this->GetGameObject();
	GOTransform* my_trans = my_go->GetTransform();
	GOTransform* sphere_trans = my_go->GetParent()->GetTransform();
	if (this_input_sys == nullptr)
		return;

	if (this_input_sys->IsKeyPressed('q') || this_input_sys->IsKeyPressed('Q'))
	{
		exit(0);
	}

	//check foword motion 'w' key
	if (this_input_sys->IsKeyPressed('w') || this_input_sys->IsKeyPressed('W'))
	{
		GOvec3 movement = this->LookAtObject->GetCalculatedLocation() - this->CamObject->GetCalculatedLocation();
		movement.y = 0;
		movement *= 0.1f;
		sphere_trans->setPosition(sphere_trans->GetPosition() + movement);
		CurrDynamicSurfaceScript->UpdatePosition(sphere_trans->GetPosition());
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


	movement_vec *= 0.01f;

	auto total_movement = my_trans->GetRotation() + movement_vec;

	//cutoff
	if (total_movement.x < -40)
	{
		total_movement.x = -40;
	}
	if (total_movement.x > 40)
	{
		total_movement.x = 40;
	}
	std::cout << total_movement.x << "," << total_movement.y << "," << total_movement.z << std::endl;
	my_trans->setRotation(total_movement);


}

void Camera3rdPerson::SCleanUp()
{
}

void DynamicSurfaceScript::SSetup(Scene* CurrScene)
{

	for (int i = -_Count.x / 2; i < _Count.x / 2; i++)
	{
		for (int j = -_Count.z / 2; j < _Count.z / 2; j++)
		{
			auto new_surface = Prefabs::GetReadySurface2d();
			if (new_surface != nullptr && new_surface->GetTransform() != nullptr)
			{
				// Calculate new position
				auto new_pos = GOvec3{ ((float)i) * _Scale.x, 0 ,((float)j) * _Scale.z };
				new_surface->GetTransform()->setPosition(new_pos);

				// Set the scale of the tile
				new_surface->GetTransform()->setScale(GOvec3{ _Scale.x, 1 ,_Scale.z });

				// Add to scene tree
				this->GetGameObject()->addChildObject(new_surface);
			}

		}
	}
}


DynamicSurfaceScript::DynamicSurfaceScript(GOvec3 Scale, GOvec3 Count)
{

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
