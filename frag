#version 330 core
in      vec4    vertexColor;
out     vec4    color;

void main()
{
	color = vec4(
	    (vertexColor.z + 1.0f) / 2.0f,
	    (vertexColor.z + 1.0f) / 2.0f,
	    (vertexColor.z + 1.0f) / 2.0f,
	    1.0f);
}