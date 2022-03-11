#pragma once

#include <string>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "SOIL2/SOIL2.h"

using namespace std;

// Useful typedefs.
typedef void (*DisplayFunc)(GLFWwindow*, double);
typedef const char *ShaderSourcePath;
typedef void (*ConfigureVAOFunc)();

// Read shader source from a file.
string readShaderSource(string filePath);

// Create a new GL program from the given shaders.
GLuint createShaderProgram(const char *vShaderSrcPath, const char *fShaderSrcPath);

// Main render loop. Call this with different display functions and vertex/fragment shaders.
void displayLoopMain(
    DisplayFunc display,
    ShaderSourcePath vShader,
    ShaderSourcePath fShader,
    int numVAOS,
    GLuint *vao,
    GLuint &renderingProgram,
    ConfigureVAOFunc vaoFunc = nullptr);
