#include "SceneRunner.h"

SceneRunner* SceneRunner::CurrentRegisteredSceneRunner = nullptr;

//fixes the current aspect ratio
void SceneRunner::FixAspectRatio()
{
	int finalW = currentWindowWidth;
	int finalH = currentWindowHeight;
	CurrentSceneWidth = currentWindowWidth;
	CurrentSceneHeight = currentWindowHeight;
	//calculate current aspect ratio
	double WinAR = (double)CurrentSceneWidth / (double)CurrentSceneHeight;
	double RefAR = (double)AspectRatioNumerator / (double)AspectRatioDenominator;

	//if window width is highr in ratio then fix it(lower it)
	if (WinAR > RefAR)
	{
		finalW = ((double)AspectRatioNumerator * (double)CurrentSceneHeight) / (double)AspectRatioDenominator;
	}
	CurrentSceneWidth = finalW;

	//if window Height is highr in ratio then fix it(lower it)
	if (WinAR < RefAR)
	{
		finalH = ((double)AspectRatioDenominator * (double)CurrentSceneWidth) / (double)AspectRatioNumerator;
	}
	CurrentSceneHeight = finalH;

	//Center view port in window
	int StartPos_X = (currentWindowWidth - finalW) / 2;
	int StartPos_Y = (currentWindowHeight - finalH) / 2;

	WindowRectBounds_x = StartPos_X;
	WindowRectBounds_y = StartPos_Y;
	WindowRectBounds_width = finalW;
	WindowRectBounds_height = finalH;
}

//Draws the scene
void SceneRunner::LoopScene()
{
	if (currentScene == nullptr)
		return;

	//run scripts
	currentScene->RunSceneScripts();

	//setup camera
	GOvec3 CamPos = GOvec3();
	GOvec3 LookAtCenter = GOvec3();
	GOvec3 LookAtUp = GOvec3();

	CamPos.x = 0;
	CamPos.y = 0;
	CamPos.z = 5;

	LookAtCenter.x = 0;
	LookAtCenter.y = 0;
	LookAtCenter.z = 0;

	LookAtUp.x = 0;
	LookAtUp.y = 1;
	LookAtUp.z = 0;

	std::vector<GameObject*> SpecialObjects;
	GOvec3 pos;
	if (currentScene != nullptr)
	{
		SpecialObjects = currentScene->GetSpecialGameObjects();
		for (int i = 0; i < SpecialObjects.size(); i++)
		{
			auto curr_special_obj = SpecialObjects.at(i);
			switch (curr_special_obj->GetGoType())
			{
			case GOCamPoint:
				pos = curr_special_obj->GetCalculatedLocation();
				CamPos.x = pos.x;
				CamPos.y = pos.y;
				CamPos.z = pos.z;
				break;

			case GOCamLookAt:
				pos = curr_special_obj->GetCalculatedLocation();
				LookAtCenter.x = pos.x;
				LookAtCenter.y = pos.y;
				LookAtCenter.z = pos.z;
				break;
			}
		}
	}

	glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-FRUSTUM_X / 2, FRUSTUM_X / 2, -FRUSTUM_Y / 2, FRUSTUM_Y / 2, 0.3, 2000.0);//todo: change to camera properties soon 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		CamPos.x, CamPos.y, CamPos.z,
		LookAtCenter.x, LookAtCenter.y, LookAtCenter.z,
		LookAtUp.x, LookAtUp.y, LookAtUp.z
	);

	//enable lights
	currentScene->TraverseLightSources();

	if (currentScene != nullptr)
	{
		for (int i = 0; i < SpecialObjects.size(); i++)
		{
			auto curr_special_obj = SpecialObjects.at(i);
			switch (curr_special_obj->GetGoType())
			{

			case GOLightSource:
				//todo: run the light
				auto ls_data = curr_special_obj->GetLightSourceData();
				auto curr_light_source_num = GL_LIGHT0 + ls_data->light_source_number;
				float in_arr[4] = { 0,0,0,0 };

				glEnable(curr_light_source_num);

				auto pos = curr_special_obj->GetTransform()->GetPosition();
				auto ambiant = ls_data->_light_ambient;
				auto diffuse = ls_data->_light_diffuse;
				auto specular = ls_data->_light_specular;

				in_arr[0] = pos.x;
				in_arr[1] = pos.y;
				in_arr[2] = pos.z;
				in_arr[3] = 0;
				glLightfv(curr_light_source_num, GL_POSITION, in_arr);

				in_arr[0] = ambiant.x;
				in_arr[1] = ambiant.y;
				in_arr[2] = ambiant.z;
				in_arr[3] = ambiant.w;
				glLightfv(curr_light_source_num, GL_AMBIENT, in_arr);

				in_arr[0] = diffuse.x;
				in_arr[1] = diffuse.y;
				in_arr[2] = diffuse.z;
				in_arr[3] = diffuse.w;
				glLightfv(curr_light_source_num, GL_DIFFUSE, in_arr);

				in_arr[0] = specular.x;
				in_arr[1] = specular.y;
				in_arr[2] = specular.z;
				in_arr[3] = specular.w;
				glLightfv(curr_light_source_num, GL_SPECULAR, in_arr);

				GLfloat param[1] = { ls_data->_GL_SPOT_CUTOFF };
				glLightfv(curr_light_source_num, GL_SPOT_CUTOFF, param);

				param[0] = ls_data->_exponent;
				glLightfv(curr_light_source_num, GL_SPOT_EXPONENT, param);

				break;

			}
		}
	}

	//draw scene
	currentScene->DrawScene();
	this->currentScene->GetSceneInputSystem()->ClearFrameInputData();

	GLenum err;
	if ((err = glGetError()) != GL_NO_ERROR)
	{
		std::cout<<err<<std::endl;
	}
	else
	{
	}
}

//Redraw callback
void SceneRunner::DisplayCallback()
{
	if (CurrentRegisteredSceneRunner == nullptr)
		return;

	//draw all three scenes on one window
	CurrentRegisteredSceneRunner->FixAspectRatio();
	glViewport(CurrentRegisteredSceneRunner->WindowRectBounds_x, CurrentRegisteredSceneRunner->WindowRectBounds_y, CurrentRegisteredSceneRunner->WindowRectBounds_width, CurrentRegisteredSceneRunner->WindowRectBounds_height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	CurrentRegisteredSceneRunner->LoopScene();
	glutSwapBuffers();
}

//window resize callback
void SceneRunner::ReshapeCallback(int w, int h)
{
	if (CurrentRegisteredSceneRunner == nullptr)
		return;
	CurrentRegisteredSceneRunner->currentWindowWidth = w;
	CurrentRegisteredSceneRunner->currentWindowHeight = h;
	glutPostRedisplay();
}

//Mouse events
void SceneRunner::MouseEventCallback(int button, int state, int x, int y)
{
	if (state == 0 || CurrentRegisteredSceneRunner == nullptr || CurrentRegisteredSceneRunner->currentScene == nullptr || CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem() == nullptr)
		return;

	auto input_sys = CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem();

	//float converted_x = ((float)x - ((float)CurrentRegisteredSceneRunner->currentWindowWidth - (float)CurrentRegisteredSceneRunner->CurrentSceneWidth) / 2) / (float)CurrentRegisteredSceneRunner->CurrentSceneWidth;
	//float converted_y = 1.0f - (((float)y - ((float)CurrentRegisteredSceneRunner->currentWindowHeight - (float)CurrentRegisteredSceneRunner->CurrentSceneHeight) / 2) / (float)CurrentRegisteredSceneRunner->CurrentSceneHeight);

	if (state == GLUT_UP)
	{
		//input_sys->EnterMouseButtonUp(button);
	}
	else
	{
		//input_sys->EnterMouseButtonDown(button);
	}
}

void SceneRunner::MouseMotionCallback(int x, int y)
{
	if (CurrentRegisteredSceneRunner == nullptr || CurrentRegisteredSceneRunner->currentScene == nullptr || CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem() == nullptr)
		return;

	int x_motion = x - CurrentRegisteredSceneRunner->currentWindowWidth / 2;

	int y_motion = y - CurrentRegisteredSceneRunner->currentWindowHeight / 2;
	glutWarpPointer(CurrentRegisteredSceneRunner->currentWindowWidth / 2, CurrentRegisteredSceneRunner->currentWindowHeight / 2);

	GOInputSystem* input_sys = CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem();

	input_sys->EnterAxisMovement(GOInputSystem::axis::X_AXIS, x_motion);
	input_sys->EnterAxisMovement(GOInputSystem::axis::Y_AXIS, y_motion);
}

void SceneRunner::MousePassiveMotionCallback(int x, int y)
{
	if (CurrentRegisteredSceneRunner == nullptr || CurrentRegisteredSceneRunner->currentScene == nullptr || CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem() == nullptr)
		return;


	int x_motion = x - CurrentRegisteredSceneRunner->currentWindowWidth / 2;

	int y_motion = y - CurrentRegisteredSceneRunner->currentWindowHeight / 2;
	glutWarpPointer(CurrentRegisteredSceneRunner->currentWindowWidth / 2, CurrentRegisteredSceneRunner->currentWindowHeight / 2);

	GOInputSystem* input_sys = CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem();

	input_sys->EnterAxisMovement(GOInputSystem::axis::X_AXIS, x_motion);
	input_sys->EnterAxisMovement(GOInputSystem::axis::Y_AXIS, y_motion);
}

//Keybard events
void SceneRunner::KeyboardEventCallback(unsigned char c, int x, int y)
{
	if (CurrentRegisteredSceneRunner == nullptr)
		return;

	CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem()->EnterCharInput(c, true);
}

//fps timer callback
void SceneRunner::timerCallback(int value) {
	glutPostRedisplay();  // Mark the current window as needing to be redisplayed
	glutTimerFunc(1000 / TARGET_FPS, timerCallback, 0);  // Register the timer callback again to achieve 60 FPS
}

SceneRunner::SceneRunner()
{
	//good enough for this project.
	//if I upgrade in the future I wont be using glut... 
	//I'll be using glfw or my own input manger using ll api using something like user32
	SceneRunner::CurrentRegisteredSceneRunner = this;
}

SceneRunner::~SceneRunner()
{
	if (this->currentScene != nullptr)
		delete currentScene;
}

void SceneRunner::SceneRunnerInit(int argc, char** argv)
{
	//call init on glut
	glutInit(&argc, argv);

	//window stuff
	CurrentSceneWidth = 1920;
	CurrentSceneHeight = 1080;
	currentWindowWidth = CurrentSceneWidth;
	currentWindowHeight = CurrentSceneHeight;

	AspectRatioNumerator = CurrentSceneWidth / std::_Gcd(CurrentSceneWidth, CurrentSceneHeight);
	AspectRatioDenominator = CurrentSceneHeight / std::_Gcd(CurrentSceneWidth, CurrentSceneHeight);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(CurrentSceneWidth, CurrentSceneHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(MY_HEADER);

	if (currentScene != nullptr)
	{
		currentScene->StartScene();
	}

	glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glDisable(GL_BLEND);
}

void SceneRunner::SetEvents()
{
	//todo change to my callbacks
	glutDisplayFunc(SceneRunner::DisplayCallback);
	glutReshapeFunc(SceneRunner::ReshapeCallback);
	glutMouseFunc(SceneRunner::MouseEventCallback);
	glutMotionFunc(SceneRunner::MouseMotionCallback);
	glutPassiveMotionFunc(SceneRunner::MousePassiveMotionCallback);
	glutKeyboardFunc(SceneRunner::KeyboardEventCallback);
	glutTimerFunc(0, SceneRunner::timerCallback, 0);
}

//start playing my beautiful scene
bool SceneRunner::RunScene(int argc, char** argv, Scene* scene_to_run)
{
	if (scene_to_run == nullptr)
		return false;
	currentScene = scene_to_run;
	this->SceneRunnerInit(argc, argv);
	this->SetEvents();
	glutMainLoop();
	return true;
}

