#version 410

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 textCoord;

out vec3 fColor;
out vec2 TextCoord;

uniform float hOffset;

void main() {
  fColor = vec3(0.2, 0.2, 0.2);
  gl_Position = vec4(hOffset + aPos.x, -aPos.y, aPos.z, 1.0);
  TextCoord = textCoord;
}
