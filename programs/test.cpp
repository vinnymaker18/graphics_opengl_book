#include <iostream>
#include <string>
#include <cstring>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "SOIL2/SOIL2.h"
#include "errors.h"
#include "utils.h"

#define numVAOS 1

using namespace std;

GLuint renderingProgram;
GLuint vao[numVAOS];

GLuint createShaderProgram() {
  string vshaderSourceStr = readShaderSource("shaders/first_vshader.vert");
  string fshaderSourceStr = readShaderSource("shaders/first_fshader.frag");

  const char *vshaderSource = vshaderSourceStr.c_str();
  const char *fshaderSource = fshaderSourceStr.c_str();

  GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
  GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);

  glShaderSource(vShader, 1, &vshaderSource, NULL);
  glShaderSource(fShader, 1, &fshaderSource, NULL);
  glCompileShader(vShader);
  glCompileShader(fShader);

  GLuint vfProgram = glCreateProgram();
  glAttachShader(vfProgram, vShader);
  glAttachShader(vfProgram, fShader);
  glLinkProgram(vfProgram);

  return vfProgram;
}

void init(GLFWwindow* window)
{
  renderingProgram = createShaderProgram();
  glGenVertexArrays(numVAOS, vao);
  glBindVertexArray(vao[0]);
}

void display(GLFWwindow *window, double currentTime)
{
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glUseProgram(renderingProgram);
  glPointSize(30.0f);
  glDrawArrays(GL_POINTS, 0, 1);
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

  GLFWwindow *window = glfwCreateWindow(600, 600, "Program 1", NULL, NULL);
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

  glfwDestroyWindow(window);
  glfwTerminate();
  exit(EXIT_SUCCESS);
};
