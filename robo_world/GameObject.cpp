#include "GameObject.h"
#include "GODrawable.h"
#include "GOScript.h"
#include "GOTransform.h"

GameObject::GameObject(GameObject* parent, std::string NewName, GOTransform* transoform)
{
	this->_parent = nullptr;
	if (parent != nullptr)
	{
		parent->AddChildObject(this);
	}
	//set parent but object is null
	this->_name = NewName;
	//this->_transoform = transoform;
	if (transoform == nullptr)
		transoform = new GOTransform();
	AttachTransform(transoform);
	this->_DrawableObject = nullptr;
	this->_script = nullptr;
}

GameObject::GameObject(GameObject* parent, std::string NewName) :GameObject(parent, NewName, nullptr) {};

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
	scripty->SetGameObjectOnce(this);
}

GOScript* GameObject::GetRunningScript()
{
	return this->_script;
}

GOTransform* GameObject::GetTransform()
{
	return this->_transoform;
}

GOTransform* GameObject::GetTransformSafe()
{
	if (this != nullptr)
		return this->GetTransform();
	else
		return nullptr;
}

void GameObject::AttachDrawable(GODrawable* new_attach)
{
	if (this->_DrawableObject != nullptr && this->_DrawableObject != new_attach)
		delete this->_DrawableObject;
	this->_DrawableObject = new_attach;
	new_attach->SetGameObjectOnce(this);
}

void GameObject::AttachScript(GOScript* new_attach)
{
	if (this->_script != nullptr && this->_script != new_attach)
		delete this->_script;
	this->_script = new_attach;
	new_attach->SetGameObjectOnce(this);
}

void GameObject::AttachTransform(GOTransform* new_attach)
{
	if (this->_transoform != nullptr && this->_transoform != new_attach)
		delete this->_transoform;
	this->_transoform = new_attach;
	new_attach->SetGameObjectOnce(this);
}

void GameObject::CalculateWorldPosition()
{
	// Set this to the identity matrix
	glm::mat4 ResultMatrixTransformation = glm::mat4(1.0f);

	GameObject* obj = this;
	while (obj != nullptr)
	{
		// Get the scale, rotation, and position of the current GameObject
		if (obj->GetTransform() != nullptr)
		{
			GOTransform* tempTransform = obj->GetTransform();
			glm::vec3 objScale = tempTransform->GetScale();
			glm::vec3 objPosition = tempTransform->GetPosition();
			glm::vec3 objRotation = tempTransform->GetRotation();

			// Convert rotation to radians
			glm::vec3 rotation = glm::vec3(glm::radians(objRotation.x), glm::radians(objRotation.y), glm::radians(objRotation.z));

			// Create transformation matrices
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), objScale);
			glm::mat4 rotateXMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotateYMatrix = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotateZMatrix = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), objPosition);

			// Combine the transformations in the correct order: scale, rotate, then translate
			glm::mat4 transformMatrix = translateMatrix * rotateZMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

			// Pre-multiply the ResultMatrixTransformation by the transformMatrix
			ResultMatrixTransformation = transformMatrix * ResultMatrixTransformation;
		}

		// Move up to the parent GameObject
		obj = obj->GetParent();
	}

	// If this GameObject has a transform, calculate its world position
	if (this->GetTransform() != nullptr)
	{
		GOTransform* tempTransform = this->GetTransform();
		glm::vec3 localPosition = tempTransform->GetPosition();

		// Convert the local position to a 4D homogeneous coordinate
		glm::vec4 localPosition4D = glm::vec4(localPosition, 1.0f);

		// Calculate the world position by multiplying with the accumulated transformation matrix
		glm::vec4 worldPosition4D = ResultMatrixTransformation * localPosition4D;
		glm::vec3 worldPosition = glm::vec3(worldPosition4D);

		// Set the calculated world position
		this->SetCalculatedPosition(worldPosition);
	}
}

bool GameObject::SetGOType(GOType new_type)
{
	bool res = true;
	static GameObject* CurrentLookAt = nullptr;
	if (new_type == GOCamLookAtPoint)//Make sure there is only one lookat
	{
		if (CurrentLookAt != nullptr)
		{
			CurrentLookAt->SetGOType(regular);
		}
		CurrentLookAt = this;
	}

	this->_GO_object_type = new_type;

	if (this->IsLightSource())//Make sure there are only eight light sources
	{
		if (this->_light_source_data == nullptr)
		{
			this->_light_source_data = new GOLightSourceData();
		}
		else
		{
			this->_GO_object_type = regular;
			res = false;
		}
	}
	return res;
}

GOType GameObject::GetGoType()
{
	return this->_GO_object_type;
}

GOLightSourceData* GameObject::GetLightSourceData()
{
	return this->_light_source_data;
}

void GameObject::SetLightSourceData(GOLightSourceData* data)
{
	if (this->_light_source_data != nullptr)
	{
		delete this->_light_source_data;
	}
	this->_light_source_data = data;
}

bool GameObject::IsLightSource()
{
	return this->_GO_object_type == GOLightSource;
}

glm::vec3 GameObject::GetCalculatedLocation()
{
	return this->_claculated_world_position;
}

void GameObject::SetCalculatedPosition(glm::vec3 new_calc_pos)
{
	this->_claculated_world_position = new_calc_pos;
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
	auto curr_script = this->GetRunningScript();
	if (curr_script != nullptr)
	{
		curr_script->CleanUp();
	}
	delete this;
}

std::string GameObject::GetName()
{
	return this->_name;
}

void GameObject::SetName(std::string new_name)
{
	this->_name = new_name;
}

std::vector<GameObject*>& GameObject::getChildren()
{
	return this->children;
}

void GameObject::SetDrawableObject(GODrawable* new_draw)
{
	this->_DrawableObject = new_draw;
}

Scene* GameObject::GetCurrentScene()
{
	return this->_attached_scene;
}

void GameObject::SetCurrentScene(Scene* curr_scene)
{
	this->_attached_scene = curr_scene;
}

GameObject* GameObject::GetParent()
{
	return this->_parent;
}

void GameObject::SetParent(GameObject* parent)
{
	if (this->GetParent() != nullptr)
	{
		this->GetParent()->RemoveChildObject(this);
	}
	parent->AddChildObject(this);
}

void GameObject::AddChildObject(GameObject* child)
{
	if (child == nullptr || child->_parent == this)
		return;

	this->children.push_back(child);
	if (child->_parent != nullptr && child->_parent != this)
	{
		child->_parent->RemoveChildObject(child);
	}
	child->_parent = this;
}

void GameObject::RemoveChildObject(GameObject* child)
{
	if (child == nullptr)
		return;
	auto it = std::find(this->children.begin(), this->children.end(),
		child);

	// If element is found found, erase it 
	if (it != this->children.end()) {
		this->children.erase(it);
	}

}
