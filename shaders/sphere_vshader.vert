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
  float z = center_z + h_radius * sin(angle);
  gl_Position = vec4(x, center_y, z, 1);
}
