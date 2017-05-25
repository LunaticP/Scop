#version 330 core

in	  vec4	vertexColor;
in	  vec4	vertexPos;
in	  float t;
out	 vec4	color;

void main()
{
//	color = vec4(
//	(1.0f + vertexColor.x) * sin(t * 10.0) - vertexPos.z / 1.5f,
//	(1.0f + vertexColor.y) * cos(t * 10.0) - vertexPos.z / 1.5f,
//	(1.0f + vertexColor.z) * -sin(t * 10.0) - vertexPos.z / 1.5f,
//	1.0);
    float   n;

    n = sqrt(vertexColor.x * vertexColor.x + vertexColor.y * vertexColor.y + vertexColor.z * vertexColor.z);
	color = vec4(n, n, n, 1.0);
}