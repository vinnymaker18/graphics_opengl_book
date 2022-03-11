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

GLuint vao;
GLuint renderingProgram;

void display(GLFWwindow *window, double curTime)
{
  glClear(GL_DEPTH_BUFFER_BIT);
  glClearColor(1.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void configureVAO()
{
  // Let's initialize a single VBO and bind it to VAO.
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // 3 vertices, 3 32-bit floating points each.
  float VERTICES[] = {-0.5, -0.5, 0, 0.5, -0.5, 0, 0, 0, 0};

  // Fill the VBO with vertex data.
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

  // Enable vertex array attributes.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);
}

int main(int argc, char **argv)
{
  // It generates and binds a VAO array and calls display in the loop by itself.
  // We need a way to configure the VAO with a VBO and 
  displayLoopMain(
      display, 
      "shaders/vao_vshader.vert",
      "shaders/vao_fshader.frag",
      1, 
      &vao,
      renderingProgram,
      configureVAO);

  return 0;
};