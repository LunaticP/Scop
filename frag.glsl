#version 330 core

in	vec4	vertexColor;
in  vec2    vertexTex;
out	vec4	color;

uniform     sampler2D   catTex;

void main()
{
	color = texture(catTex, vertexTex);
}