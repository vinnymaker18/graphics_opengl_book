#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "utils.h"

using namespace std;

// Useful typedefs.
string readShaderSource(string filePath)
{
  ifstream fin(filePath);
  ostringstream out;
  while (!fin.eof()) {
    string line;
    getline(fin, line);
    out << line << endl;
  }

  fin.close();

  return out.str();
}

GLuint createShaderProgram(const char *vShaderSrcPath, const char *fShaderSrcPath)
{
  string vshaderSourceStr = readShaderSource(vShaderSrcPath);
  string fshaderSourceStr = readShaderSource(fShaderSrcPath);

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

  glDeleteShader(vShader);
  glDeleteShader(fShader);
  return vfProgram;
}

void init(GLFWwindow* window, ShaderSourcePath vShader, ShaderSourcePath fShader, 
    int numVAOS, GLuint *vao, GLuint& renderingProgram)
{
  renderingProgram = createShaderProgram(vShader, fShader);
  glUseProgram(renderingProgram);
  glGenVertexArrays(numVAOS, vao);
  glBindVertexArray(vao[0]);
}

void displayLoopMain(DisplayFunc display, ShaderSourcePath vShader, ShaderSourcePath fShader,
    int numVAOS, GLuint *vao, GLuint& renderingProgram, ConfigureVAOFunc configureVAO)
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

  init(window, vShader, fShader, numVAOS, vao, renderingProgram);
  if (configureVAO != nullptr) {
    configureVAO();
  }
  while (!glfwWindowShouldClose(window)) {
    display(window, glfwGetTime());
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwDestroyWindow(window);
  glfwTerminate();
}
