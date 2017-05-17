#version 330 core

layout (location = 0) in vec3 position;

out     vec4    vertexColor;
uniform float   time;

void main()
{
	gl_Position = vec4(
	position.x * cos(time) + position.z * sin(time),
	position.y,
	-position.x * sin(time) + position.z * cos(time),
	1.0f);
	vertexColor = vec4(
	position.x * cos(time) + position.z * sin(time),
	position.y,
	-position.x * sin(time) + position.z * cos(time),
	1.0f);
}