#pragma once
#include "stdafx.h"
#include "Scene.h"

//macros
#define MY_NAME "Netanel Cohen Gindi"
#define MY_HEADER "Robo-World"
#define TARGET_FPS 60
#define FRUSTUM_X 5.0f
#define FRUSTUM_Y 5.0f

static int x_last;
static int y_last;

class SceneRunner {
private:
	//window sizing and aspect ration
	int scale_x_start = -960;
	int scale_x_end = 960;
	int scale_y_start = -540;
	int scale_y_end = 540;
	int scale_z_start = 960;
	int scale_z_end = -960;

	int AspectRatioNumerator = 1920;
	int AspectRatioDenominator = 1080;
	int currentWindowWidth = 1920;
	int currentWindowHeight = 1080;
	int CurrentSceneWidth = 1920;
	int CurrentSceneHeight = 1080;

	int WindowRectBounds_x = 0;
	int WindowRectBounds_y = 0;
	int WindowRectBounds_width = 0;
	int WindowRectBounds_height = 0;
	Scene* currentScene = nullptr;

	//functions
	void SceneRunnerInit(int argc, char** argv);
	void SetEvents();
	void FixAspectRatio();
	void LoopScene();

	//glut callbacks

	static SceneRunner* CurrentRegisteredSceneRunner;
	static void DisplayCallback();
	static void ReshapeCallback(int w, int h);
	static void MouseEventCallback(int button, int state, int x, int y);
	static void KeyboardEventCallback(unsigned char c, int x, int y);
	static void timerCallback(int value);
	static void MouseMotionCallback(int x, int y);
	static void MousePassiveMotionCallback(int x, int y);
public:
	SceneRunner();
	~SceneRunner();
	bool RunScene(int argc, char** argv, Scene*);
};
//The main func to run my beautiful scene
