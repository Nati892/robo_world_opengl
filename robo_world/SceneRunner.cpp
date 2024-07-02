#include "SceneRunner.h"

//macros
#define MY_NAME "Netanel Cohen Gindi"
#define MY_HEADER "Robo-World"
#define TARGET_FPS 60
#define FRUSTUM_X 2
#define FRUSTUM_Y 2

//window sizing and aspect ration
int scale_x_start = -960;
int scale_x_end = 960;
int scale_y_start = -540;
int scale_y_end = 540;
int scale_z_start = 960;
int scale_z_end = -960;

int AspectRatioNumerator;
int AspectRatioDenominator;
int currentWindowWidth;
int currentWindowHeight;
int CurrentSceneWidth = 1920;
int CurrentSceneHeight = 1080;

int WindowRectBounds_x = 0;
int WindowRectBounds_y = 0;
int WindowRectBounds_width = 0;
int WindowRectBounds_height = 0;
AnimationTimer* timer;
Scene* PlayScene;
//scene control and animation structs

void CleanupAndExit()
{
	exit(0);
}

//fixes the current aspect ratio
void FixAspectRatio()
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

//CubeObject* obj;
//Draws the scene
void LoopScene()
{
	if (PlayScene == nullptr)
		return;

	//run scripts
	PlayScene->RunSceneScripts();

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
	if (PlayScene != nullptr)
	{
		SpecialObjects = PlayScene->GetSpecialGameObjects();
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

	glFrustum(-FRUSTUM_X / 2, FRUSTUM_X / 2, -FRUSTUM_Y / 2, FRUSTUM_Y / 2, 0.4, 200.0);//todo: change to camera properties soon 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		CamPos.x, CamPos.y, CamPos.z,
		LookAtCenter.x, LookAtCenter.y, LookAtCenter.z,
		LookAtUp.x, LookAtUp.y, LookAtUp.z
	);

	//enable lights
	PlayScene->TraverseLightSources();

	if (PlayScene != nullptr)
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
				break;
			}

		}
	}

	//draw scene
	PlayScene->DrawScene();
}

//Redraw callback
void DisplayCallback()
{
	//draw all three scenes on one window
	FixAspectRatio();
	glViewport(WindowRectBounds_x, WindowRectBounds_y, WindowRectBounds_width, WindowRectBounds_height);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	LoopScene();
	glutSwapBuffers();
}

//window resize callback
void ReshapeCallback(int w, int h)
{
	currentWindowWidth = w;
	currentWindowHeight = h;
	glutPostRedisplay();
}

//Mouse events
void MouseEventCallback(int button, int state, int x, int y)
{
	if (state == 0)
		return;
	float converted_x = ((float)x - ((float)currentWindowWidth - (float)CurrentSceneWidth) / 2) / (float)CurrentSceneWidth;
	float converted_y = 1.0f - (((float)y - ((float)currentWindowHeight - (float)CurrentSceneHeight) / 2) / (float)CurrentSceneHeight);
}

//Keybard events
void KeyboardEventCallback(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'a'://left object
	case 'A':
		break;

	case 'D'://right object
	case 'd':
		break;

	case '+'://faster animation
		break;

	case '-'://slower animation
		break;

	case 'c'://change perspective type
	case 'C':
		break;

	case 'q':
	case 'Q':
		exit(0);
		break;
	}

}

void timerCallback(int value) {
	glutPostRedisplay();  // Mark the current window as needing to be redisplayed
	glutTimerFunc(1000 / TARGET_FPS, timerCallback, 0);  // Register the timer callback again to achieve 60 FPS
}


//my initiation function
void MyInit(int argc, char** argv)
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
	PlayScene = GetSampleScene();
	if (PlayScene != nullptr)
	{
		PlayScene->StartScene();

	}
	//run startup scripts

	timer = new AnimationTimer(10, 0, 360);
	timer->StartTimer();
	//set startup settings

	glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering
	glEnable(GL_LIGHTING);
	glShadeModel(GL_FLAT);
}

//set system/input events
void SetEvents()
{
	glutDisplayFunc(DisplayCallback);
	glutReshapeFunc(ReshapeCallback);
	glutMouseFunc(MouseEventCallback);
	glutKeyboardFunc(KeyboardEventCallback);
	glutTimerFunc(0, timerCallback, 0);
}

//start play my beautiful scene
void RunScene(int argc, char** argv)
{
	MyInit(argc, argv);
	SetEvents();
	glutMainLoop();
}