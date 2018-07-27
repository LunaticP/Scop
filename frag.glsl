#version 330 core

in	vec4	vertexColor;
in	vec4	vertexPos;
in	float	t;
out	vec4	color;

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
	color = col(vertexPos);
	vec4 pos = vertexPos;
	if (vertexColor == vec4(0.0)) {
//		col(vertexColor)i;
//	    pos = vec4(
//	    pos.x * cos(t) + pos.z * sin(t),
//	    pos.y,
//	    pos.x * -sin(t) + pos.z * cos(t),
//	1.0);
        color = pos / vec4(1.0, 4.0, 1.0, 1.0) * vec4(4.5);
//		color = vec4(vec3(0.2), 1.0) + col(vec4(1.0 - color.x, 1.0 - color.y, 1.0 - color.z, 1.0));
	}
	else
	    color = vec4(0.0);
}