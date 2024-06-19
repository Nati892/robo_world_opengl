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