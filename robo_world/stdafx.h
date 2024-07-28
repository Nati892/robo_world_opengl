#pragma once

// if you dont know what does this stdafx.h do, here is a link to read about it,
// its basiclly a cool trick that shortens compilation time and development
// https://stackoverflow.com/questions/4726155/what-is-stdafx-h-used-for-in-visual-studio

//Adding this like renia asked for cross platform support
#ifdef _WIN32

#include <GL/freeglut.h>
#pragma comment(lib, "freeglut.lib")

#else

#ifdef __APPLE__

#include <GLUT / glut.h>

#else

#include <GL/glut.h>

#endif

#endif

#define GLM_ENABLE_EXPERIMENTAL
//std
#include <string>
#include <iostream>
#include <chrono>
#include <cmath>
#include <vector>
#include <string>
#include <map>
#include <filesystem>
#include <stack>

//glm
#include "glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtc/type_ptr.hpp>
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/constants.hpp"
#include <glm/gtx/quaternion.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "tiny_obj_loader.h"

//imgui
#include "imgui.h"
#include "imgui_impl_glut.h"
#include "imgui_impl_opengl2.h"

//self 
#include "Loaders.h"

//macros
#define LIGHT_SOURCES_NUM 8