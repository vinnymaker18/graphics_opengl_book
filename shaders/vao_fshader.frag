#version 410

uniform vec4 inputColor;

in vec3 fColor;
out vec4 color;
in vec2 TextCoord;

uniform sampler2D ourTexture;

void main() {
  color = texture(ourTexture, TextCoord);
}
