#pragma once

#include <string>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "SOIL2/SOIL2.h"

using namespace std;

// Read shader source from a file.
string readShaderSource(string filePath);


// Create a new GL program from the given shaders.
GLuint createShaderProgram(const char *vShaderSrcPath, const char *fShaderSrcPath);
