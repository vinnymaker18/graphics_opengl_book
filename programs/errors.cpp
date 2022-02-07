#include <iostream>

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "SOIL2/SOIL2.h"

using namespace std;

bool checkOpenGLError()
{
  bool found = false;
  while (true) {
    int glError = glGetError();
    if (glError == GL_NO_ERROR) {
      break;
    }

    found = true;
    cerr << "OpenGL Error : " << glError << endl;
  }

  return found;
}

void printShaderLog(GLuint shader)
{
  int len = 0;
  glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
  if (len > 0) {
    int numCharsWritten;
    char *log = (char *) malloc(len); 
    glGetShaderInfoLog(shader, len, &numCharsWritten, log);
    cerr << "Shader Info log : " << log << endl;
    free(log);
  }
}

void printProgramLog(GLuint program)
{
  int len = 0;
  glGetProgramiv(program, GL_INFO_LOG_LENGTH, &len);
  if (len > 0) {
    int numCharsWritten;
    char *log = (char *) malloc(len); 
    glGetProgramInfoLog(program, len, &numCharsWritten, log);
    cerr << "Program Info log : " << log << endl;
    free(log);
  }
}
