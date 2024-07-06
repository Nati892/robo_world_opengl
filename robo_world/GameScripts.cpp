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

	int x_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::X_AXIS);
	int y_movement = this_input_sys->GetMouseAxisMovement(GOInputSystem::axis::Y_AXIS);
	auto movement_vec = GOvec3{ 0,0,0 };
	if (x_movement != 0)
	{
		movement_vec += GOvec3{ 0,static_cast<float>(x_movement),0 };
	}
	if (y_movement != 0)
	{
		movement_vec += GOvec3{ static_cast<float>(y_movement),0,0 };
	}


	movement_vec *= 0.01f;

	auto total_movement=my_trans->GetRotation() + movement_vec;
	
	//cutoff
	if (total_movement.x < -40)
	{
		total_movement.x = -40;
	}
	if (total_movement.x > 40)
	{
		total_movement.x =40;
	}
	std::cout << total_movement.x << "," << total_movement.y << "," << total_movement.z << std::endl;
	my_trans->setRotation(total_movement);


}

void Camera3rdPerson::SCleanUp()
{
}
