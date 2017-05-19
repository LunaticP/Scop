#version 330 core

layout (location = 0) in vec3 position;

out	 vec4	vertexColor;
out	 vec4	vertexPos;
out  float  t;
uniform float   time;
uniform float   ratiox;
uniform float   ratioy;

void main()
{
    vec4 pos;

    pos = vec4(
    position.x * cos(time) + position.z * sin(time),
    position.y,
    position.x * -sin(time) + position.z * cos(time),
    1.0);

	gl_Position = vec4 (
	pos.x / ((ratiox > 1.0) ? ratiox : 1.0),
	pos.y / ((ratioy > 1.0) ? ratioy : 1.0),
	pos.z, 1.0);

	vertexColor = vec4 (position.x, position.y, position.z, 1.0);
	vertexPos = vec4 (gl_Position.x, gl_Position.y, gl_Position.z, 1.0);
	t = time;
}