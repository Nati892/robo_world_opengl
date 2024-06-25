#include "GameScripts.h"

void BasicAxisRotateScript::SSetup()
{
	rotate_timer = new AnimationTimer(10, 0, 360);//todo: add cleanup func for this
	color_timer = new AnimationTimer(5, 1, 255);//todo: add cleanup func this
	rotate_timer->StartTimer();
	color_timer->StartTimer();
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
		my_draw->setDiffuseColor(curr_new_red_val, 0, 0, curr_diff[3]);
	}

	if (my_trans != nullptr)
	{
		auto curr_rot = my_trans->getRotation();
		switch (_rotation_axis)
		{
		case axis_x:
			my_trans->setRotation(val, curr_rot[1], curr_rot[2]);
			break;
		case axis_y:
			my_trans->setRotation(curr_rot[0], val, curr_rot[2]);
			break;
		case axis_z:
			my_trans->setRotation(curr_rot[0], curr_rot[1], val);
			break;
		default:
			_rotation_axis = axis_x;
			break;
		}
	}
}

void BasicAxisRotateScript::SCleanUp()
{
	delete rotate_timer;
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
