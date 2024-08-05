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

GameObject* Prefabs::GetNewRobot(std::string name)
{
	GameObject* player_go = new GameObject(nullptr, name);
	GameObject* body_container = new GameObject(player_go,"flip_container");
	GameObject* player_object = Prefabs::GetNewHead("player_head");
	body_container->AddChildObject(player_object);
	player_object->GetTransform()->setPosition(0, -1, 0);

	GameObject* player_torso = Prefabs::GetNewTorso("player_torso");
	body_container->AddChildObject(player_torso);
	player_torso->GetTransform()->setPosition(0, -3, 0);

	//Add MoveVecStartTrans and MoveVecEndTrans to torso
	auto MoveVecStart = new GameObject(player_torso,"MoveVecStart");
	auto MoveVecEnd = new GameObject(player_torso,"MoveVecEnd");
	MoveVecStart->SetGOType(GOSpecialGeneral);
	MoveVecEnd->SetGOType(GOSpecialGeneral);
	MoveVecStart->GetTransform()->setPosition(0,0,0);
	MoveVecEnd->GetTransform()->setPosition(-1,0,0);

	GameObject* WheelsHolder = new GameObject(body_container, "wheels_holder");
	WheelsHolder->GetTransform()->setPosition(0.4, -4.5, 0);
	auto scripty = new BasicAxisRotateScript();
	scripty->SetRotationAxis(axis_z);
	WheelsHolder->AttachScript(scripty);

	//create and add left wheel to holder
	auto wheel = Prefabs::GetNewWheel("left_wheel");
	wheel->GetTransform()->setRotation(0, 90, 0);
	wheel->GetTransform()->setPosition(0, 0, -0.7);
	WheelsHolder->AddChildObject(wheel);

	//create and add right wheel to holder
	wheel = Prefabs::GetNewWheel("right_wheel");
	WheelsHolder->AddChildObject(wheel);
	wheel->GetTransform()->setRotation(0, 270, 0);
	wheel->GetTransform()->setPosition(0, 0, 0.7);

	//create and add arms
	GameObject* right_hand_holder = new GameObject(body_container, "robot_right_arm_holder");

	auto right_hand = Prefabs::GetNewRobotArm("right_hand");

	right_hand_holder->AddChildObject(right_hand);
	right_hand_holder->GetTransform()->setPosition(0.4, -2.3, -1.3);
	right_hand_holder->GetTransform()->setRotation(0, 180, 0);
	right_hand_holder->GetTransform()->setScale(1, 1, -1);

	return player_go;
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
	ret_child->GetTransform()->setPosition(0, -8, 0);
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

GameObject* Prefabs::GetNewRobotArm(std::string name)
{
	//hand_holder<-arm<-forarm<-hand
	GameObject* hand_holder = new GameObject(nullptr, name);
	GameObject* hand_holder2 = new GameObject(hand_holder, "hand_fix_transform");

	GameObject* arm_go = Prefabs::GetNewSimpleModel("robo_arm", "robot_arm.obj", "");
	GameObject* forarm_go = Prefabs::GetNewSimpleModel("robo_forarm", "robot_forarm.obj", "metal_texture.jpg");
	GameObject* hand_go = Prefabs::GetNewSimpleModel("robo_hand", "robot_hand.obj", "metal_texture.jpg");

	forarm_go->GetTransform()->setPosition(-0.575, 0, 0);
	hand_go->GetTransform()->setPosition(-0.63, 0, 0.04);
	hand_holder2->GetTransform()->setScale(-1, 1, 1);

	hand_holder2->AddChildObject(arm_go);
	arm_go->AddChildObject(forarm_go);
	forarm_go->AddChildObject(hand_go);

	return hand_holder;
}


GameObject* Prefabs::GetNewRandomTree(std::string name)
{
	GameObject* go = new GameObject(nullptr, name, nullptr);

	int randomIndex = (rand() % 6) + 1;//pick tree bark
	std::string tree_bark_texture = "tree_bark_texture" + std::to_string(randomIndex) + ".jpg";

	randomIndex = (rand() % 8) + 1;//pick tree bark
	std::string tree_l_texture = "tree_l_texture" + std::to_string(randomIndex) + ".jpg";

	auto tree_go = Prefabs::GetNewSimpleModel("tree", "tree1.obj", std::vector<std::string> { tree_bark_texture, tree_l_texture });
	go->AddChildObject(tree_go);

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

	BasicAxisRotateScript* scripty = new BasicAxisRotateScript();
	int rand_speed = (rand() % 18) +2;//pick tree bark
	scripty->SetSpeed(rand_speed);
	ret->AttachScript(scripty);
	return ret;
}

GameObject* Prefabs::GetReadyAmbiantLightSource(std::string name)
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, name, light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0.6,0.6,0.6,1 };
	ldata->_light_diffuse = { 0,0,0,1 };
	ldata->_light_specular = { 0,0,0,1 };
	return ret;
}

GameObject* Prefabs::GetReadySunLightSource(std::string name)
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, name, light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0,0,0,1 };
	ldata->_light_diffuse = { 0.8,0.8,0.8,1 };
	ldata->_light_specular = { 1,1,1,1 };
	ldata->_spot_direction = {-1,-1,-1};
	ldata->_spotlight_cuttoff = {180};
	ldata->_shininess = 64;
	return ret;
}

GameObject* Prefabs::GetReadyDiffuseLightSource(std::string name)
{
	GOTransform* light_trans = new GOTransform();
	GameObject* ret = new GameObject(nullptr, name, light_trans);
	ret->SetGOType(GOLightSource);
	auto ldata = ret->GetLightSourceData();
	ldata->_light_ambient = { 0,0,0,1 };
	ldata->_light_diffuse = { 0.3,0.3,0.3,1 };
	ldata->_light_specular = { 0.3,0.3,0.3,1 };

	auto light_sphere = new GameObject(ret,"light_sphere");
	light_sphere->AttachDrawable(new DrawLightSphere());
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
	ldata->_light_specular = { 1,1,1,1 };
	ldata->_exponent = 3;
	ldata->_spot_direction = { -1, -1, -1 };
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
	ldata->_light_diffuse = { 0,0.6,0.6,1 };
	ldata->_light_specular = { 0.5,0.5,0.5,1 };
	ldata->_spotlight_cuttoff = 180;
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

GameObject* Prefabs::GetReadyCheckboardSurface2d(std::string name)
{
	GOTransform* surface2d_trans = new GOTransform();
	GameObject* surface2d_obj = new GameObject(nullptr, "surface2d", surface2d_trans);

	DrawCheckBoardSurface2d* surface2d_drawable = new DrawCheckBoardSurface2d();
	surface2d_obj->AttachDrawable(surface2d_drawable);
	return surface2d_obj;
}

GameObject* Prefabs::GetReadyDynamicSurface2d(std::string name)
{
	GOTransform* surface2d_trans = new GOTransform();
	GameObject* surface2d_obj = new GameObject(nullptr, name, surface2d_trans);

	surface2d_obj->AttachScript(new DynamicSurfaceScript(glm::vec3{ 10, 0, 10 }, glm::vec3{ 20,0,20 }));
	return surface2d_obj;
}

GameObject* Prefabs::GetReadyCheckBoardDynamicSurface2d(std::string name)
{
	GOTransform* surface2d_trans = new GOTransform();
	GameObject* surface2d_obj = new GameObject(nullptr, name, surface2d_trans);

	surface2d_obj->AttachScript(new DynamicSurfaceScript(glm::vec3{ 10, 0, 10 }, glm::vec3{ 20,0,20 },false));
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

	Box->AddChildObject(wall1);
	Box->AddChildObject(wall2);
	Box->AddChildObject(wall3);
	Box->AddChildObject(wall4);
	Box->AddChildObject(wall5);

	wall1->GetTransform()->setRotation(90, 270, 0);
	wall1->GetTransform()->setPosition(0, 40, -100);
	wall1->GetTransform()->setScale(100, 1, 200);
	wall1->GetDrawableObject()->setAmbientColor(1, 1, 1, 1);
	wall1->GetDrawableObject()->setDiffuseColor(0, 0, 0, 1);
	wall1->GetDrawableObject()->setSpecularColor(0, 0, 0, 1);

	wall2->GetTransform()->setRotation(270, 90,0);
	wall2->GetTransform()->setPosition(0, 40, 100);
	wall2->GetTransform()->setScale(100, 1, 200);
	wall2->GetDrawableObject()->setDiffuseColor(0, 0, 0, 1);
	wall2->GetDrawableObject()->setSpecularColor(0, 0, 0, 1);

	wall3->GetTransform()->setRotation(180, 0, 90);
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


GameObject* Prefabs::GetNewMushroom(std::string name)
{
	GameObject* go = new GameObject(nullptr, name, nullptr);
	auto muhs_obj = Prefabs::GetNewSimpleModel(name, "mushroom1.obj", "mushroom_texture.jpg");
	go->AddChildObject(muhs_obj);

	muhs_obj->GetTransform()->setPosition(5, 0.4, 5);
	muhs_obj->GetTransform()->setRotation(-90, 0, 0);
	return go;
}

GameObject* Prefabs::GetNewSimpleModel(std::string name, std::string model_name, std::string texture)
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

	ret_child->AttachDrawable(new GoDrawble3d(model_name, "", textures));
	return ret;
}

GameObject* Prefabs::GetNewWheel(std::string name)
{
	auto obj = Prefabs::GetNewSimpleModel(name, "wheel.obj", "metal_texture.jpg");
	return obj;
}
