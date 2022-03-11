# TODO - Replace this with a Makefile.

# e.g.,
# include "GLFW/glfw3.h", "glm/glm.hpp" "GL/glew.h" "SOIL2/SOIL2.h"
g++ -I libs/glfw-3.3.6/include -I libs/glm -I libs/glew/include -I libs/soil2/src -I common\
  -L libs/glfw-3.3.6/build/src -L libs/soil2/lib/macosx -L libs/glew/lib\
  -l glfw -l GLEW -l soil2-debug\
  -framework OpenGL\
  -o $2\
  common/errors.cpp common/utils.cpp\
  $1

# Need to set DYLD_LIBRARY_PATH before we can run the binaries.
