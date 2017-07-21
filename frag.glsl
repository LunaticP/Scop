#version 330 core

in	  vec4	vertexColor;
in	  vec4	vertexPos;
in	  float t;
out	 vec4	color;

vec4	col(vec4 vec){
	float	big;
	float	ratio;

	if (vec.x > vec.y && vec.x > vec.z)
		big = vec.x;
	else if (vec.y > vec.x && vec.y > vec.z)
		big = vec.y;
	else
		big = vec.z;
	ratio = 1.0 / big;
	return (vec * ratio);
}

void main()
{
//	color = vec4(
//	(1.0f + vertexColor.x) * sin(t * 10.0) - vertexPos.z / 1.5f,
//	(1.0f + vertexColor.y) * cos(t * 10.0) - vertexPos.z / 1.5f,
//	(1.0f + vertexColor.z) * -sin(t * 10.0) - vertexPos.z / 1.5f,
//	1.0);
    float   n;

	color = col(vertexPos);
	if (vertexColor == vec4(0.0)) {
//    	n = sqrt(vertexColor.x * vertexColor.x + vertexColor.y * vertexColor.y + vertexColor.z * vertexColor.z);
//		color = vec4(vec3(n / 2.0 + 0.3), 1.0);
		color = col(vec4(1.0 - color.x, 1.0 - color.y, 1.0 - color.z, 1.0));
	}
}