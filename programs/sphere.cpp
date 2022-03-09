#include <iostream>
#include <string>
#include <cstring>
#include <utility>

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

// Keep PLANES odd, one for the central plane and rest equally divided b/w upper and lower 
// hemispheres.
const int PLANES = 99;
const int POINTS_PER_PLANE = 30;

void display(GLFWwindow *window, double currentTime)
{
  glClear(GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(renderingProgram);

  const double rad = 0.4, cx = 0, cy = 0, cz = 0;
  for (double p = -(PLANES / 2.0);p <= (PLANES / 2.0); p += 1.0) {
    double seg = (rad) / (PLANES / 2.0);
    double h = seg * abs(p);
    double xc = cx, yc = cy + seg * p, zc = cz;
    double rc = sqrt(rad * rad - h * h);

    double theta = 2 * M_PI / POINTS_PER_PLANE;

    GLuint offsetTheta = glGetUniformLocation(renderingProgram, "theta");
    GLuint offsetCX = glGetUniformLocation(renderingProgram, "center_x");
    GLuint offsetCY = glGetUniformLocation(renderingProgram, "center_y");
    GLuint offsetCZ = glGetUniformLocation(renderingProgram, "center_z");
    GLuint offsetHR = glGetUniformLocation(renderingProgram, "h_radius");
    GLuint offsetNP = glGetUniformLocation(renderingProgram, "POINTS");

    glProgramUniform1f(renderingProgram, offsetTheta, theta);
    glProgramUniform1f(renderingProgram, offsetHR, rc);
    glProgramUniform1f(renderingProgram, offsetCX, xc);
    glProgramUniform1f(renderingProgram, offsetCY, yc);
    glProgramUniform1f(renderingProgram, offsetCZ, zc);
    glProgramUniform1i(renderingProgram, offsetNP, POINTS_PER_PLANE);

    glDrawArrays(GL_LINE_LOOP, 0, POINTS_PER_PLANE);
  }
}

int main(int argc, char **argv)
{
  displayLoopMain(display,
                  "shaders/sphere_vshader.vert",
                  "shaders/sphere_fshader.frag",
                  numVAOS, vao, renderingProgram);
};
