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

	//run scnee gui
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize.x = 1600;
	io.DisplaySize.y = 900;

	//static bool show_demo_window = true;
	//static bool show_another_window = true;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	ImGui::NewFrame();
	for (auto win : currentScene->GetGuiWindows())
	{
		win->ShowGUI(currentScene);
	}

	ImGui::Render();
	glViewport(0, 0, (GLsizei)io.DisplaySize.x, (GLsizei)io.DisplaySize.y);
	currentScene->UpdateTime();

	//run scripts
	currentScene->RunSceneScripts();

	//setup camera
	glm::vec3 CamPos = glm::vec3();
	glm::vec3 LookAtCenter = glm::vec3();
	glm::vec3 LookAtUp = glm::vec3();

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
	glm::vec3 pos;
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
				std::cout << "cam vec:" << CamPos.x << "|" << CamPos.y << "|" << CamPos.z << std::endl;
				break;

			case GOCamLookAtPoint:
				pos = curr_special_obj->GetCalculatedLocation();
				LookAtCenter.x = pos.x;
				LookAtCenter.y = pos.y;
				LookAtCenter.z = pos.z;
				std::cout << "lookat vec:" << LookAtCenter.x << "|" << LookAtCenter.y << "|" << LookAtCenter.z << std::endl;
				break;
			}
		}
	}

	glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
	glLoadIdentity();

	glFrustum(-FRUSTUM_X / 8.0f, FRUSTUM_X / 8.0f, -FRUSTUM_Y / 8.0f, FRUSTUM_Y / 8.0f, 0.3, 2000.0);//todo: change to camera properties soon 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	currentScene->cameraPosition = CamPos;
	currentScene->cameraTarget = LookAtCenter;
	currentScene->cameraUp = LookAtUp;

	//Todo delete
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

				in_arr[0] = ls_data->_spot_direction.x;
				in_arr[1] = ls_data->_spot_direction.y;
				in_arr[2] = ls_data->_spot_direction.z;
				glLightfv(curr_light_source_num, GL_SPOT_DIRECTION, in_arr);

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
		std::cout << "err:" << err << std::endl;
	}


	//draw gui
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
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
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGLUT_MouseFunc(button, state, x, y);
	if (io.WantCaptureKeyboard)
	{
		return;
	}

	if (state == 0 || CurrentRegisteredSceneRunner == nullptr || CurrentRegisteredSceneRunner->currentScene == nullptr || CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem() == nullptr)
		return;

	auto input_sys = CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem();

}

void SceneRunner::MouseMotionCallback(int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGLUT_MotionFunc(x, y);
	if (io.WantCaptureKeyboard)
	{
		return;
	}
	if (CurrentRegisteredSceneRunner == nullptr || CurrentRegisteredSceneRunner->currentScene == nullptr || CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem() == nullptr)
		return;

	int x_motion = x - CurrentRegisteredSceneRunner->currentWindowWidth / 2;

	int y_motion = y - CurrentRegisteredSceneRunner->currentWindowHeight / 2;
	if (lock_mouse) {
		glutWarpPointer(CurrentRegisteredSceneRunner->currentWindowWidth / 2, CurrentRegisteredSceneRunner->currentWindowHeight / 2);
	}

	GOInputSystem* input_sys = CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem();

	input_sys->EnterAxisMovement(GOInputSystem::axis::X_AXIS, x_motion);
	input_sys->EnterAxisMovement(GOInputSystem::axis::Y_AXIS, y_motion);
}

void SceneRunner::MousePassiveMotionCallback(int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGLUT_MotionFunc(x, y);
	if (io.WantCaptureKeyboard)
	{
		return;
	}
	if (CurrentRegisteredSceneRunner == nullptr || CurrentRegisteredSceneRunner->currentScene == nullptr || CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem() == nullptr)
		return;

	int x_motion = x - CurrentRegisteredSceneRunner->currentWindowWidth / 2;

	int y_motion = y - CurrentRegisteredSceneRunner->currentWindowHeight / 2;
	if (lock_mouse) {
		glutWarpPointer(CurrentRegisteredSceneRunner->currentWindowWidth / 2, CurrentRegisteredSceneRunner->currentWindowHeight / 2);
	}
	GOInputSystem* input_sys = CurrentRegisteredSceneRunner->currentScene->GetSceneInputSystem();

	input_sys->EnterAxisMovement(GOInputSystem::axis::X_AXIS, x_motion);
	input_sys->EnterAxisMovement(GOInputSystem::axis::Y_AXIS, y_motion);
}

//Keybard events
void SceneRunner::KeyboardEventCallback(unsigned char c, int x, int y)
{
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGLUT_KeyboardFunc(c, x, y);
	if (io.WantCaptureKeyboard)
	{
		return;
	}


	if (CurrentRegisteredSceneRunner == nullptr)
		return;

	if (c == 'e' || c == 'E')
	{
		lock_mouse = !lock_mouse;
		if (lock_mouse)
		{
			glutSetCursor(GLUT_CURSOR_NONE);
		}
		else
		{
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
	}
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
	lock_mouse = true;
	//call init on glut
	glutInit(&argc, argv);

	//window stuff
	CurrentSceneWidth = 1600;
	CurrentSceneHeight = 900;
	currentWindowWidth = CurrentSceneWidth;
	currentWindowHeight = CurrentSceneHeight;

	AspectRatioNumerator = CurrentSceneWidth / std::_Gcd(CurrentSceneWidth, CurrentSceneHeight);
	AspectRatioDenominator = CurrentSceneHeight / std::_Gcd(CurrentSceneWidth, CurrentSceneHeight);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);

	//imgui init
	if (!IMGUI_CHECKVERSION())
	{
		std::cout << "imgui is not supported! for some reason..." << std::endl;
		return;
	}
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	ImGui::StyleColorsDark();
	ImGui_ImplGLUT_Init();
	ImGui_ImplOpenGL2_Init();
	ImGui_ImplGLUT_InstallFuncs();

	//glut window
	glutInitWindowSize(CurrentSceneWidth, CurrentSceneHeight);
	glutInitWindowPosition(0, 0);
	glutCreateWindow(MY_HEADER);

	if (currentScene != nullptr)
	{
		currentScene->StartScene();
	}

	glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering
	glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glDepthFunc(GL_LESS);
	glDisable(GL_BLEND);

	glDisable(GL_LIGHT0);
	glDisable(GL_LIGHT1);
	glDisable(GL_LIGHT2);
	glDisable(GL_LIGHT3);
	glDisable(GL_LIGHT4);
	glDisable(GL_LIGHT5);
	glDisable(GL_LIGHT6);
	glDisable(GL_LIGHT7);

	GLfloat globalAmbient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbient);
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

	//cleanup imgui
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplGLUT_Shutdown();
	ImGui::DestroyContext();

	return true;
}

