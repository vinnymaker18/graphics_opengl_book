#version 410

uniform float center_x;
uniform float center_y;
uniform float center_z;
uniform float h_radius;
uniform float theta;

uniform int POINTS;

void main(void)
{
  float angle = theta * gl_VertexID;
  float x = center_x + h_radius * cos(angle);
  float y = center_y + h_radius * sin(angle);
  gl_Position = vec4(x, y, center_z, 1);
}
