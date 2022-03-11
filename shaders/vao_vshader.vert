#version 410

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;

out vec3 fColor;

uniform float hOffset;

void main() {
  fColor = color;
  gl_Position = vec4(hOffset + aPos.x, -aPos.y, aPos.z, 1.0);
}
