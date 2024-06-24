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

template <typename T>
void GameObject::SetGOScript()
{
	static_assert(std::is_base_of<GOScript, T>::value, "T must inherit from GOscript!");
	GOScript* scripty = nullptr;

	scripty = new T();
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

GODrawable* GameObject::GetDrawableObject()
{
	return this->_DrawableObject;
}

std::vector<GameObject*>& GameObject::getChildren()
{
	// TODO: insert return statement here
	return this->children;
}

void GameObject::addChildObject(GameObject* child)
{
	children.push_back(child);
}