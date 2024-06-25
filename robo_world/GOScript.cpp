#include "GOScript.h"

void GOScript::SSetup()
{
}

void GOScript::SetupOnce()
{
	if (_started)
		return;

	this->SSetup();
	_started = true;
}

void GOScript::SLoop()
{
}

GameObject* GOScript::GetGameObject()
{
	return this->_GameObject;
}

void GOScript::SetGameObjectOnce(GameObject* go_head)
{
	if (this->_GameObject == nullptr)
		this->_GameObject = go_head;
}
