#pragma once
#include "stdafx.h"

//singleton object
class GOInputSystem
{
private:
	static GOInputSystem* _instance;
	GOInputSystem();
	~GOInputSystem();

public:
	void CleanUp();
	GOInputSystem* GetInstance();
	bool IsMouseButtonDown(int button);
	bool IsKeyPressed(char key);
	void ClearFrameInputData();

};