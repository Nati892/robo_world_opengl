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

CubeObject* obj;
//Draws the scene
void LoopScene()
{
	glMatrixMode(GL_MODELVIEW | GL_PROJECTION);
	glLoadIdentity();


	glFrustum(-FRUSTUM_X / 2, FRUSTUM_X / 2, -FRUSTUM_Y / 2, FRUSTUM_Y / 2, 0.4, 200.0);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		0, 0, 3,
		0, 0, 0,
		0, 1, 0);

	//add lighting here
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);

	GLfloat light_position1[] = { -10.0, 15.0, -10.0, 0.0 };  // Light position
	GLfloat light_position2[] = { 0.0, 15.0, 0.0, 0.0 };  // Light position
	GLfloat light_position3[] = { 10.0, 15.0, 10.0, 0.0 };  // Light position
	GLfloat light_ambient[] = { 0.8, 0.8, 0.8, 1.0 };  // Ambient light
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };  // Diffuse light
	GLfloat light_zeros[] = { 0, 0, 0, 1.0 };  // Diffuse light

	glLightfv(GL_LIGHT0, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_zeros);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position2);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

	glLightfv(GL_LIGHT1, GL_POSITION, light_position3);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);

	auto val = timer->GetCurrentAnimationValue();
	auto sceneChildren = PlayScene->GetChildren();

	auto first_child = sceneChildren.at(0);
	first_child->setRotation(0,val,0);

	auto second_child = first_child->getChildren().at(0);
	second_child->setRotation(0,0, val);

	if (PlayScene != nullptr)
	{
		PlayScene->DrawScene();
	}
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
	PlayScene = GetTestScene();

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