#include "Prefabs.h"
#include "GOTransform.h"
#include "GOScript.h"
#include "GameScripts.h"
#include "Drawables.h"
GameObject* Prefabs::GetNewRotatingCube(std::string name)
{
	GameObject* ret = nullptr;
	ret = new GameObject(nullptr, name, nullptr);

	//create transform for game object
	GOTransform* trans = new GOTransform();
	ret->AttachTransform(trans);

	//attach drawable
	DrawCube* cube = new DrawCube();
	ret->AttachDrawable(cube);

	//attach script
	GOScript* scripty = new BasicAxisRotateScript();
	ret->AttachScript(scripty);

	return ret;
}

GameObject* Prefabs::GetNewSphere(std::string name)
{
	GameObject* ret = nullptr;

	ret = new GameObject(nullptr, name, nullptr);

	//create transform for game object
	GOTransform* trans = new GOTransform();
	ret->AttachTransform(trans);

	//attach drawable
	DrawSphere* sphere = new DrawSphere();
	ret->AttachDrawable(sphere);

	return ret;
}

GameObject* Prefabs::GetNewHead(std::string name)
{
	GameObject* ret = new GameObject(nullptr, name, nullptr);
	GameObject* ret_child = new GameObject(ret, name, nullptr);

	ret_child->AttachDrawable(new GoDrawble3d("head.obj", "metal_texture.jpg"));
	ret_child->GetTransform()->setRotation(180, 90, 0);
	ret_child->GetTransform()->setPosition(0, -9, 0);
	ret_child->GetTransform()->setScale(3, 3, 3);

	return ret;
}

GameObject* Prefabs::GetNewTorso(std::string name)
{
	GameObject* ret = new GameObject(nullptr, name, nullptr);
	GameObject* ret_child = new GameObject(ret, name, nullptr);

	ret_child->AttachDrawable(new GoDrawble3d("torso.obj", "metal_texture.jpg"));
	ret_child->GetTransform()->setScale(3, 3, 3);
	ret_child->GetTransform()->setPosition(0, -6, 0);
	ret_child->GetTransform()->setRotation(180, 90, 0);
	return ret;
}

GameObject* Prefabs::GetNewRobotLeg(std::string name)
{
	GameObject* ret = new GameObject(nullptr, name, nullptr);
	GameObject* ret_child = new GameObject(ret, name, nullptr);

	ret_child->AttachDrawable(new GoDrawble3d("robot_leg.obj", "metal_texture.jpg"));
	ret_child->GetTransform()->setScale(3, 3, 3);
	ret_child->GetTransform()->setPosition(0, -6, 0);
	ret_child->GetTransform()->setRotation(180, 90, 0);

	
	return ret;
}

GameObject* Prefabs::GetNewTree1(std::string name)
{
	GameObject* go = new GameObject(nullptr,name,nullptr);
	auto tree_go = Prefabs::GetNewSimpleModel("tree", "realistic_tree.obj",  std::vector<std::string> { "clay_texture.jpg", "surface_board_texture.jpg", "metal_texture.jpg" });
	//auto tree_go = Prefabs::GetNewSimpleModel("tree", "realistic_tree.obj", "middle.jpg");
	go->addChildObject(tree_go);

	tree_go->GetTransform()->setPosition(0, 0, 0);
	tree_go->GetTransform()->setRotation(-90,0,0);
	go->GetTransform()->setPosition(0,0,15);
	return go;
}

GameObject* Prefabs::GetNewRotatingSphere(std::string name)
{
	GameObject* ret = nullptr;

	ret = new GameObject(nullptr, name, nullptr);

	//create transform for game object
	GOTransform* trans = new GOTransform();
	ret->AttachTransform(trans);

	//attach drawable
	DrawSphere* sphere = new DrawSphere();
	ret->AttachDrawable(sphere);

	//attach script
	GOScript* scripty = new BasicAxisRotateScript();
	ret->AttachScript(scripty);
	return ret;
}

GameObject* Prefabs::GetNewRotatingteapot(std::string name)
{
	auto ret = Prefabs::GetReadyTeapot(name);

	GOScript* scripty = new BasicAxisRotateScript();
	ret->AttachScript(scripty);
	return ret;
}

GameObject* Prefabs::GetReadyAmbiantLightSource(std::string name)
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, name, light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0.4,0.4,0.4,1 };
	ldata->_light_diffuse = { 0.0,0.0,0.0,1 };
	ldata->_light_specular = { 0,0,0,1 };
	return ret;
}

GameObject* Prefabs::GetReadyDiffuseLightSource(std::string name)
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, name, light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0,0,0,1 };
	ldata->_light_diffuse = { 0.6,0.6,0.6,1 };
	ldata->_light_specular = { 0,0,0,1 };
	return ret;
}

GameObject* Prefabs::GetReadySpecularLightSource(std::string name)
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, name, light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0,0,0,1 };
	ldata->_light_diffuse = { 0,0,0,1 };
	ldata->_light_specular = { 0.6,0.6,0.6,1 };
	return ret;
}

GameObject* Prefabs::GetReadyLightSource(std::string name)
{
	GOTransform* light_trans = new GOTransform();
	light_trans->setPosition(0, 100, 0);
	GameObject* ret = new GameObject(nullptr, name, light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0.4,0.4,0.4,1 };
	ldata->_light_diffuse = { 0.6,0.6,0.6,1 };
	ldata->_light_specular = { 0.5,0.5,0.5,1 };
	ldata->_GL_SPOT_CUTOFF = 180;
	ldata->_shininess = 1;
	ldata->_spot_direction = { 0,-10,0 };
	ldata->_exponent = 5;
	return ret;
}

GameObject* Prefabs::GetReadyCubeGameObject(std::string name)
{
	GOTransform* cube_trans = new GOTransform();
	GameObject* cube_obj = new GameObject(nullptr, name, cube_trans);

	DrawCube* cube_drawable = new DrawCube();
	cube_obj->AttachDrawable(cube_drawable);
	return cube_obj;
}

GameObject* Prefabs::GetReadyTeapot(std::string name)
{
	GameObject* cube_obj = new GameObject(nullptr, name, nullptr);

	DrawTeapot* draw_teapot = new DrawTeapot();
	cube_obj->AttachDrawable(draw_teapot);
	return cube_obj;
}

GameObject* Prefabs::GetReadySurface2d(std::string name, std::string texture)
{
	GOTransform* surface2d_trans = new GOTransform();
	GameObject* surface2d_obj = new GameObject(nullptr, "surface2d", surface2d_trans);

	DrawSurface2d* surface2d_drawable = new DrawSurface2d(texture);
	surface2d_obj->AttachDrawable(surface2d_drawable);
	return surface2d_obj;
}

GameObject* Prefabs::GetReadyDynamicSurface2d(std::string name)
{
	GOTransform* surface2d_trans = new GOTransform();
	GameObject* surface2d_obj = new GameObject(nullptr, name, surface2d_trans);

	surface2d_obj->AttachScript(new DynamicSurfaceScript(GOvec3{ 10, 0, 10 }, GOvec3{ 20,0,20 }));
	return surface2d_obj;
}


GameObject* Prefabs::GetReadySkyBox(std::string name, std::string FollowObject)
{
	GameObject* Box = new GameObject(nullptr, name, nullptr);
	auto wall1 = Prefabs::GetReadySurface2d("left", "left.jpg");
	auto wall2 = Prefabs::GetReadySurface2d("right", "right.jpg");
	auto wall3 = Prefabs::GetReadySurface2d("back", "back.jpg");
	auto wall4 = Prefabs::GetReadySurface2d("middle", "middle.jpg");
	auto wall5 = Prefabs::GetReadySurface2d("up", "up.jpg");

	Box->addChildObject(wall1);
	Box->addChildObject(wall2);
	Box->addChildObject(wall3);
	Box->addChildObject(wall4);
	Box->addChildObject(wall5);

	wall1->GetTransform()->setRotation(90, 0, 270);
	wall1->GetTransform()->setPosition(0, 40, -100);
	wall1->GetTransform()->setScale(100, 1, 200);
	wall1->GetDrawableObject()->setAmbientColor(1, 1, 1, 1);
	wall1->GetDrawableObject()->setDiffuseColor(0, 0, 0, 1);
	wall1->GetDrawableObject()->setSpecularColor(0, 0, 0, 1);

	wall2->GetTransform()->setRotation(270, 0, 270);
	wall2->GetTransform()->setPosition(0, 40, 100);
	wall2->GetTransform()->setScale(100, 1, 200);
	wall2->GetDrawableObject()->setDiffuseColor(0, 0, 0, 1);
	wall2->GetDrawableObject()->setSpecularColor(0, 0, 0, 1);

	wall3->GetTransform()->setRotation(180, 0, 270);
	wall3->GetTransform()->setPosition(100, 40, 0);
	wall3->GetTransform()->setScale(100, 1, 200);
	wall3->GetDrawableObject()->setDiffuseColor(0, 0, 0, 1);
	wall3->GetDrawableObject()->setSpecularColor(0, 0, 0, 1);

	wall4->GetTransform()->setRotation(180, 180, 90);
	wall4->GetTransform()->setPosition(-100, 40, 0);
	wall4->GetTransform()->setScale(100, 1, 200);
	wall4->GetDrawableObject()->setDiffuseColor(0, 0, 0, 1);
	wall4->GetDrawableObject()->setSpecularColor(0, 0, 0, 1);

	wall5->GetTransform()->setRotation(180, 180, 0);
	wall5->GetTransform()->setPosition(0, 90, 0);
	wall5->GetTransform()->setScale(200, 1, 200);
	wall5->GetDrawableObject()->setDiffuseColor(0, 0, 0, 1);
	wall5->GetDrawableObject()->setSpecularColor(0, 0, 0, 1);
	Box->AttachScript(new SkyBoxScript(FollowObject));

	return Box;
}


GameObject* Prefabs::GetNewSimpleModel(std::string name, std::string model_name,std::string texture)
{
	GameObject* ret = new GameObject(nullptr, name, nullptr);
	GameObject* ret_child = new GameObject(ret, name, nullptr);

	ret_child->AttachDrawable(new GoDrawble3d(model_name, texture));

	return ret;
}

GameObject* Prefabs::GetNewSimpleModel(std::string name, std::string model_name, std::vector<std::string> textures)
{
	GameObject* ret = new GameObject(nullptr, name, nullptr);
	GameObject* ret_child = new GameObject(ret, name, nullptr);

	ret_child->AttachDrawable(new GoDrawble3d(model_name,"", textures));

	return ret;
}