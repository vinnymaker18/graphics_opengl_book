#version 410
out vec4 color;
void main(void)
{
  if (gl_FragCoord.x < 600) color = vec4(1, 1, 1, 1); else color = vec4(0, 0, 1, 1);
}
