#pragma once

// if you dont know what does this stdafx.h do, here is a link to read about it,
// its basiclly a cool trick that shortens compilation time and development
// https://stackoverflow.com/questions/4726155/what-is-stdafx-h-used-for-in-visual-studio

//Adding this like renia asked for cross platform support
#ifdef _WIN32

#include "glut.h"
#pragma comment(lib, "glut32.lib")

#else

#ifdef __APPLE__

#include <GLUT / glut.h>

#else

#include <GL/glut.h>

#endif

#endif

#include <string>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "TextureLoader.h"

//macros
#define LIGHT_SOURCES_NUM 8

struct GOvec3 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;

	GOvec3& operator+=(GOvec3 other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		return *this;
	}

	GOvec3& operator-=(GOvec3 other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		return *this;
	}

	GOvec3& operator*=(float a)
	{
		this->x *= a;
		this->y *= a;
		this->z *= a;
		return *this;
	}

	GOvec3& operator+=(float a)
	{
		this->x += a;
		this->y += a;
		this->z += a;
		return *this;
	}

	GOvec3& operator-=(float a)
	{
		this->x -= a;
		this->y -= a;
		this->z -= a;
		return *this;
	}


	GOvec3 operator+(GOvec3 other)
	{
		GOvec3 ret = { this->x, this->y, this->z };
		ret += other;
		return ret;
	}

	GOvec3 operator-(GOvec3 other)
	{
		GOvec3 ret = { this->x, this->y, this->z };
		ret -= other;
		return ret;
	}

	GOvec3 operator+(float a)
	{
		GOvec3 ret = { this->x, this->y, this->z };
		ret += a;
		return *this;
	}

	GOvec3 operator-(float a)
	{
		GOvec3 ret = { this->x, this->y, this->z };
		ret -= a;
		return *this;
	}
};

struct GOvec4 {
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	float w = 0.0f;

	GOvec4& operator+=(GOvec4 other)
	{
		this->x += other.x;
		this->y += other.y;
		this->z += other.z;
		this->w += other.w;
		return *this;
	}

	GOvec4& operator-=(GOvec4 other)
	{
		this->x -= other.x;
		this->y -= other.y;
		this->z -= other.z;
		this->w -= other.w;
		return *this;
	}

	GOvec4& operator*=(float a)
	{
		this->x *= a;
		this->y *= a;
		this->z *= a;
		this->w *= a;
		return *this;
	}
};
