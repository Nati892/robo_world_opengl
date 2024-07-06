#pragma once
#include "stdafx.h"
class GOInputSystem
{
public:
	enum axis { X_AXIS, Y_AXIS };

	GOInputSystem();
	~GOInputSystem();

	// Query for inputs
	bool IsMouseButtonDown(int button);
	int GetMouseAxisMovement(axis ax);
	bool IsKeyPressed(char key);
	void ClearFrameInputData(); // Clears all data in the table for inputs

	// Methods to update input states
	void EnterCharInput(char key, bool);
	void EnterAxisMovement(axis ax, float movement);
	void EnterMouseButtonDown(int button);
	void EnterMouseButtonUp(int button);
private:
	std::map<char, bool> keyState; // Stores key states
	std::map<int, bool> mouseButtonState; // Stores mouse button states
	float mouseXMovement;
	float mouseYMovement;
};
