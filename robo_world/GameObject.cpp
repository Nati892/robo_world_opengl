#include "GameObject.h"
#include "GODrawable.h"
#include "GOScript.h"
#include "GOTransform.h"


GameObject::GameObject(GameObject* parent, std::string NewName, GOTransform* transoform)
{
	this->_parent = parent;
	if (this->_parent != nullptr)
		this->_parent->addChildObject(this);
	this->_name = NewName;
	this->_transoform = transoform;
	this->_DrawableObject = nullptr;
	this->_script = nullptr;
}

GameObject::~GameObject()
{
	if (this->_DrawableObject != nullptr)
	{
		this->_DrawableObject->CleanUp();
	}

	if (this->_transoform != nullptr)
	{
		this->_transoform->CleanUp();
	}

	if (this->_script != nullptr)
	{
		this->_script->CleanUp();
		delete this->_script;
	}

	if (this->_light_source_data != nullptr)
	{
		delete this->_light_source_data;
	}
}

void GameObject::SetGOScript(GOScript* scripty)
{
	this->_script = scripty;
}

GOScript* GameObject::GetRunningScript()
{
	return this->_script;
}

GOTransform* GameObject::GetTransform()
{
	return this->_transoform;
}

void GameObject::AttachDrawable(GODrawable* new_attach)
{
	if (this->_DrawableObject != nullptr)
		delete this->_DrawableObject;
	this->_DrawableObject = new_attach;
	new_attach->SetGameObjectOnce(this);
}

void GameObject::AttachScript(GOScript* new_attach)
{
	if (this->_script != nullptr)
		delete this->_script;
	this->_script = new_attach;
	new_attach->SetGameObjectOnce(this);
}

void GameObject::AttachTransform(GOTransform* new_attach)
{
	if (this->_transoform != nullptr)
		delete this->_transoform;
	this->_transoform = new_attach;
	new_attach->SetGameObjectOnce(this);
}

void GameObject::SetGOType(GOType new_type, int light_number)
{
	if (this->_GO_object_type == GOLightSource && new_type != GOLightSource)
	{
		if (this->_light_source_data != nullptr)
		{
			delete this->_light_source_data;
		}
	}

	this->_GO_object_type = new_type;

	if (!this->IsLightSource())
	{
		this->_GO_object_type = GOLightSource;
		if (this->_light_source_data == nullptr)
		{
			this->_light_source_data = new GOLightSourceData();
		}
	}
}//todo continue working on light etc

GOLightSourceData* GameObject::GetLightSourceData()
{
	return this->_light_source_data;
}

bool GameObject::IsLightSource()
{
	return this->_GO_object_type == GOLightSource;
}

void GameObject::SetTransform(GOTransform* set_trans)
{
	this->_transoform = set_trans;
}

GODrawable* GameObject::GetDrawableObject()
{
	return this->_DrawableObject;
}

void GameObject::Destroy(bool deep)
{
	//do for all children first with inherited deep clean
	if (deep)
	{
		auto children = this->getChildren();
		for (int i = 0; i < children.size(); i++)
		{
			GameObject* curr_child = children.at(i);
			curr_child->Destroy(true);
		}
	}
	delete this;
}

std::vector<GameObject*>& GameObject::getChildren()
{
	// TODO: insert return statement here
	return this->children;
}

void GameObject::SetDrawableObject(GODrawable* new_draw)
{
	this->_DrawableObject = new_draw;
}

void GameObject::addChildObject(GameObject* child)
{
	children.push_back(child);
	child->_parent = this;
}