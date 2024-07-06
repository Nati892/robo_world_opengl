#include "GOInputSystem.h"

GOInputSystem::GOInputSystem() : mouseXMovement(0), mouseYMovement(0)
{
}

GOInputSystem::~GOInputSystem()
{
}

bool GOInputSystem::IsMouseButtonDown(int button)
{
    auto it = mouseButtonState.find(button);
    if (it != mouseButtonState.end())
    {
        return it->second;
    }
    return false;
}

int GOInputSystem::GetMouseAxisMovement(axis ax)
{
    if (ax == X_AXIS)
    {
        return mouseXMovement;
    }
    else if (ax == Y_AXIS)
    {
        return mouseYMovement;
    }
    return 0.0f;
}

bool GOInputSystem::IsKeyPressed(char key)
{
    auto it = keyState.find(key);
    if (it != keyState.end())
    {
        return true;
    }
    return false;
}

void GOInputSystem::ClearFrameInputData()
{
    keyState.clear();
    mouseButtonState.clear();
    mouseXMovement = 0;
    mouseYMovement = 0;
}

void GOInputSystem::EnterCharInput(char key,bool input=true)
{
    keyState[key] = input;
}

void GOInputSystem::EnterAxisMovement(axis ax, float movement)
{
    if (ax == X_AXIS)
    {
        mouseXMovement += movement;
    }
    else if (ax == Y_AXIS)
    {
        mouseYMovement += movement;
    }
}

void GOInputSystem::EnterMouseButtonDown(int button)
{
    mouseButtonState[button] = true;
}

void GOInputSystem::EnterMouseButtonUp(int button)
{
    mouseButtonState[button] = false;
}