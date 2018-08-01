#version 330 core

#define M_PI 3.1415926535897932384626433832795

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texture;

out		vec3	vertexNormal;
out     vec2    vertexTex;

uniform	float	time;
uniform	mat4	model;
uniform	mat4	proj;

void main()
{
	gl_Position = proj * model * vec4(
	position.x * cos(time) + position.z * sin(time),
	position.y,
	position.x * -sin(time) + position.z * cos(time),
	1.0);
    vertexNormal = normalize(normal);
	vertexTex = texture;
}