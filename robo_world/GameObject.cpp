#include "GameObject.h"



GameObject::GameObject(GameObject* parent, std::string NewName, GOTransform* transoform)
{
	this->_parent = parent;
	this->_name = NewName;
	this->_transoform = transoform;
	this->_DrawableObject = nullptr;
	this->_script = nullptr;
}

GameObject::~GameObject()
{
}

void GameObject::SetGOScript(GOScript* scripty)
{
	if (scripty == nullptr)
		return;

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

void GameObject::SetTransform(GOTransform* set_trans)
{
	this->_transoform = set_trans;
}

GODrawable* GameObject::GetDrawableObject()
{
	return this->_DrawableObject;
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
}