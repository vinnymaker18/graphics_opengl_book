#include <iostream>
#include <string>
#include <cstring>
#include <utility>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "SOIL2/SOIL2.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "errors.h"
#include "utils.h"

using namespace std;

GLuint vao;
GLuint renderingProgram;

float hOffset = 0, incr = 0.02;

void display(GLFWwindow *window, double curTime)
{
  double gray = 0.75;
  glClearColor(gray, gray, gray, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  double greenValue = sin(curTime) / 2.0f + 0.5f;
  double blueValue = cos(curTime) / 2.0f + 0.5f;
  double redValue = cos(2 * curTime + 3) / 2.0f + 0.5f;
  GLuint inputColorLocation = glGetUniformLocation(renderingProgram, "inputColor");
  GLuint hOffsetLocation = glGetUniformLocation(renderingProgram, "hOffset");
  glUniform4f(inputColorLocation, redValue, greenValue, blueValue, 1.0);
  glUniform1f(hOffsetLocation, hOffset);
  hOffset += incr;
  if (hOffset > 1 || hOffset < -1)
    incr = -incr;

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void configureVAO()
{
  // Let's initialize a single VBO and bind it to VAO.
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // 4 vertices, 8 32-bit floating points each - 3 for coords, 3 for color, 2 for texture coords
  float VERTICES[] = {-0.45, 0.45, 0.0, 1.0, 0.0, 0.0, 0, 1,
                      -0.45, -0.45, 0.0, 0.0, 1.0, 0.0, 0, 0,
                       0.45, -0.45, 0.0, 0.0, 0.0, 1.0, 1, 0,
                       0.45, 0.45, 0.0, 0.5, 0.5, 0.5, 1, 1};

  // Fill the VBO with vertex data.
  glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES), VERTICES, GL_STATIC_DRAW);

  // Enable vertex array attributes.
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Create a single EBO and bind it.
  GLuint EBO;
  glGenBuffers(1, &EBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  int indices[] = {0, 1, 2, 0, 3, 2};
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  // Create a single texture object, load an image and generate texture image.
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  // load image data from a jpg file.
  int width, height, numChannels;
  unsigned char *data = stbi_load("images/pic.jpg", &width, &height, &numChannels, 0);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  // free image data.
  stbi_image_free(data);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);
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
