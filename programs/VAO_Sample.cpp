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
  double gray = 0.75;
  glClearColor(gray, gray, gray, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  double greenValue = sin(curTime) / 2.0f + 0.5f;
  double blueValue = cos(curTime) / 2.0f + 0.5f;
  double redValue = cos(2 * curTime + 3) / 2.0f + 0.5f;
  GLuint inputColorLocation = glGetUniformLocation(renderingProgram, "inputColor");
  glUniform4f(inputColorLocation, redValue, greenValue, blueValue, 1.0);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void configureVAO()
{
  // Let's initialize a single VBO and bind it to VAO.
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // 4 vertices, 6 32-bit floating points each - 3 for coords, 3 for color
  float VERTICES[] = {-0.5, -0.5, 0.0, 1.0, 0.0, 0.0,
                       0.5, -0.5, 0.0, 0.0, 1.0, 0.0,
                       0.0, 0.0, 0.0, 0.0, 0.0, 1.0,
                       0.0, -1.0, 0.0, 0.5, 0.5, 0.5};

  // Fill the VBO with vertex data.
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

  // Enable vertex array attributes.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Create a single EBO and bind it.
  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  int indices[] = {0, 1, 2, 0, 1, 3};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
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
