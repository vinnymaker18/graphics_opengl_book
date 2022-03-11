# TODO - Replace this with a Makefile.

# e.g.,
# include "GLFW/glfw3.h", "glm/glm.hpp" "GL/glew.h" "SOIL2/SOIL2.h"
g++ -I glfw-3.3.6/include -I glm -I glew/include -I soil2/src -I programs\
  -L glfw-3.3.6/build/src -L soil2/lib/macosx -L glew/lib\
  -l glfw -l GLEW -l soil2-debug\
  -framework OpenGL\
  -o $2\
  programs/errors.cpp programs/utils.cpp\
  $1

# Need to set DYLD_LIBRARY_PATH before we can run the binaries.
