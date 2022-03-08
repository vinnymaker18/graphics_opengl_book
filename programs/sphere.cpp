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

// Keep PLANES odd, one for the central plane and rest equally divided b/w upper and lower 
// hemispheres.
const int PLANES = 21;
const int POINTS_PER_PLANE = 30;

pair<double*, double*> getSpherePoints(double cx, double cy, double cz, double rad)
{

  double *xcoords = new double[PLANES * POINTS_PER_PLANE];
  double *ycoords = new double[PLANES * POINTS_PER_PLANE];
  int index = 0;

  for (int p = -(PLANES / 2);p < PLANES / 2; p++) {
    double seg = (rad) / (PLANES / 2);
    double xc = cx, yc = cy, zc = cz + p * seg;
    double h = seg * abs(p);
    double rc = sqrt(rad * rad - h * h);

    double theta = 2 * M_PI / POINTS_PER_PLANE;
    for (int i = 0;i < POINTS_PER_PLANE; i++) {
      double x = xc + rc * cos(theta);
      double y = yc + rc * sin(theta);

      xcoords[index] = x;
      ycoords[index] = y;
      index++;
    }
  }

  return make_pair(xcoords, ycoords);
}

void init(GLFWwindow *window)
{
}

void display(GLFWwindow *window, double currentTime)
{
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

int main(int argc, char **argv)
{
  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow *window = glfwCreateWindow(600, 600, "Sphere", NULL, NULL);
  int actualWidth = 100, actualHeight = 200;
  glfwGetFramebufferSize(window, &actualWidth, &actualHeight);
  glfwMakeContextCurrent(window);
  glViewport(0, 0, actualWidth, actualHeight);
  glewExperimental = GL_TRUE;
  if (GLEW_OK != glewInit()) {
    exit(EXIT_FAILURE);
  }

  glfwSwapInterval(1);

  init(window);
  while (!glfwWindowShouldClose(window)) {
    display(window, glfwGetTime());
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  return 0;
};
