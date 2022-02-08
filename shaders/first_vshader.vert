#version 410
uniform float offset_x;
uniform float offset_y;
uniform float offset_z;

void main(void)
{
  float x = 0.25, y = 0.25, z = 0.0, w = 1.0;
  if (gl_VertexID == 0) {
    y = -y;
  } else if (gl_VertexID == 1) {
    x = -x;
    y = -y;
  }

  gl_Position = vec4(x + offset_x, y + offset_y, z + offset_z, w);
}
