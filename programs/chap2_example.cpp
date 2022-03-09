#include <iostream>
#include <string>
#include <cstring>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "SOIL2/SOIL2.h"
#include "errors.h"
#include "utils.h"

using namespace std;

#define numVAOS 1

GLuint renderingProgram;
GLuint vao[numVAOS];

void incr(float& x, float& inc)
{
  x += inc;
  if (x > 1.0 || x < -1.0)
    inc = -inc;
}

void display(GLFWwindow *window, double currentTime)
{
  static float x = 0.0, y = 0.0, z = 0.0;
  static float inc_x = 0.015, inc_y = 0.021, inc_z = 0.01;

  glClear(GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(renderingProgram);
  
  incr(x, inc_x);
  incr(y, inc_y);
  incr(z, inc_z);

  GLuint offsetXLoc = glGetUniformLocation(renderingProgram, "offset_x");
  GLuint offsetYLoc = glGetUniformLocation(renderingProgram, "offset_y");
  GLuint offsetZLoc = glGetUniformLocation(renderingProgram, "offset_z");

  glProgramUniform1f(renderingProgram, offsetXLoc, x);
  glProgramUniform1f(renderingProgram, offsetYLoc, y);
  glProgramUniform1f(renderingProgram, offsetZLoc, z);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main(int argc, char **argv)
{
  displayLoopMain(display, "shaders/first_vshader.vert", "shaders/first_fshader.frag",
                  numVAOS, vao, renderingProgram);
  return 0;
};
