#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include "utils.h"

using namespace std;

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

  return vfProgram;
}
