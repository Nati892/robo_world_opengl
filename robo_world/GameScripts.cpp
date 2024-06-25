#include "GameScripts.h"

void BasicXRotateScript::SSetup()
{
	rotate_timer = new AnimationTimer(10, 0, 360);//todo: add cleanup func for this
	color_timer = new AnimationTimer(5, 1, 255);//todo: add cleanup func this
	rotate_timer->StartTimer();
	color_timer->StartTimer();
}

void BasicXRotateScript::SLoop()
{
	auto val = rotate_timer->GetCurrentAnimationValue();
	auto val2 = color_timer->GetCurrentAnimationValue();
	GameObject* my_go = this->GetGameObject();
	GODrawable* my_draw = my_go->GetDrawableObject();
	GOTransform* my_trans = my_go->GetTransform();

	if (my_draw != nullptr)
	{
		float curr_new_red_val = (((float)val2)/(255.0f));
		auto curr_diff=my_draw->getDiffuseColor();
		auto curr_ambiant=my_draw->getAmbientColor();

		my_draw->setDiffuseColor(curr_new_red_val, 0, 0, curr_diff[3]);
	}

	if (my_trans != nullptr)
	{
		auto curr_rot = my_trans->getRotation();
		my_trans->setRotation(val, curr_rot[1], curr_rot[2]);
	}
}
