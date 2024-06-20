#pragma once
#include "stdafx.h"
#include "DrawableObject.h"

class CubeObject :public virtual DrawableObject
{

public:
	CubeObject();
	~CubeObject();
	virtual void DrawObject();
};