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

void GameObject::CalculateWorldPosition()
{
	if (this->GetGoType() != regular)
		return;

	// Set this to the identity matrix
	glm::mat4 ResultMatrixTransformation = glm::mat4(1.0f);

	GameObject* obj = this;
	while (obj->GetParent() != nullptr)
	{
		obj = obj->GetParent();

		// Get the scale, rotation, and position of the current GameObject
		if (obj->GetTransform() != nullptr)
		{
			GOTransform* tempTransform = obj->GetTransform();
			GOvec3 objScale = tempTransform->GetScale();
			GOvec3 objPosition = tempTransform->GetPosition();
			GOvec3 objRotation = tempTransform->GetRotation();

			glm::vec3 scale = glm::vec3(objScale.x, objScale.y, objScale.z);
			glm::vec3 position = glm::vec3(objPosition.x, objPosition.y, objPosition.z);
			glm::vec3 rotation = glm::vec3(objRotation.x, objRotation.y, objRotation.z);

			// Create transformation matrices
			glm::mat4 scaleMatrix = glm::scale(glm::mat4(1.0f), scale);
			glm::mat4 rotateXMatrix = glm::rotate(glm::mat4(1.0f), rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
			glm::mat4 rotateYMatrix = glm::rotate(glm::mat4(1.0f), rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
			glm::mat4 rotateZMatrix = glm::rotate(glm::mat4(1.0f), rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
			glm::mat4 translateMatrix = glm::translate(glm::mat4(1.0f), position);

			// Combine the transformations in the correct order: scale, rotate, then translate
			glm::mat4 transformMatrix = translateMatrix * rotateZMatrix * rotateYMatrix * rotateXMatrix * scaleMatrix;

			// Multiply with the ResultMatrixTransformation and store in ResultMatrixTransformation
			ResultMatrixTransformation = transformMatrix * ResultMatrixTransformation;
		}
		if (this->GetTransform() != nullptr)
		{
			GOTransform* tempTransform = this->GetTransform();
			GOvec3 objPosition = tempTransform->GetPosition();
			glm::vec3 position = glm::vec3(objPosition.x, objPosition.y, objPosition.z);
			// Convert the local position to a 4D homogeneous coordinate
			glm::vec4 localPosition4D = glm::vec4(position, 1.0f);

			glm::vec3 claculated_position = ResultMatrixTransformation * localPosition4D;
			tempTransform->setPosition(claculated_position.x, claculated_position.y, claculated_position.z);
		}
	}

	// Use the ResultMatrixTransformation as needed, e.g., setting it to the SpecialObject's world transformation

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
}

GOType GameObject::GetGoType()
{
	return this->_GO_object_type;
}

GOLightSourceData* GameObject::GetLightSourceData()
{
	return this->_light_source_data;
}

bool GameObject::IsLightSource()
{
	return this->_GO_object_type == GOLightSource;
}

GOvec3 GameObject::GetCalculatedLocation()
{
	return GOvec3();
}

void GameObject::SetCalculatedPosition(GOvec3 new_calc_pos)
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

GameObject* GameObject::GetParent()
{
	return this->_parent;
}

void GameObject::addChildObject(GameObject* child)
{
	children.push_back(child);
	child->_parent = this;
}