#include "GOScript.h"

void GOScript::SSetup()
{
	//empty, to be overriden
}

GOScript::~GOScript()
{
	//clear script from the game object
	GameObject* this_go = this->GetGameObject();
	if (this_go != nullptr)
	{
		GOScript* curr_script = this_go->GetRunningScript();
		if (this == curr_script)
		{
			this_go->SetGOScript(nullptr);
		}
	}
}

void GOScript::CleanUp()
{
	this->SCleanUp();
	delete this;
}

void GOScript::SCleanUp()
{
	//empty, to be overriden
}

void GOScript::SLoop()
{
	//empty, to be overriden
}

void GOScript::SetupOnce()
{
	if (_started)
		return;

	this->SSetup();
	_started = true;
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
