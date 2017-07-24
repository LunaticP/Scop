#version 330 core

#define M_PI 3.1415926535897932384626433832795

layout (location = 0) in vec3 position;

out		vec4	vertexColor;
out		vec4	vertexPos;
out		float	t;
uniform	bool	mod;
uniform	float	time;
uniform	float	ratiox;
uniform	float	ratioy;

float   pix(float pos, float time, float rat)
{
	float   s;
	float   val;

	s = ((sin(time) + 1.0) / 2.0) * rat;
	val = round(pos * s);
	return (val / s);
}

void main()
{
	vec4 pos;
	float value;

	pos = vec4(position / 5.0, 1.0);
	pos.y -= 0.0;
	if (mod)
		vertexColor = pos;
	else
		vertexColor = vec4(0.0);

	pos = vec4(
	pos.x * cos(time) + pos.z * sin(time),
	pos.y,
	pos.x * -sin(time) + pos.z * cos(time),
	1.0);

	pos = vec4(
	pos.x,
	pos.y * cos(0.0) - pos.z * sin(0.0),
	pos.y * sin(0.0) + pos.z * cos(0.0),
	1.0);

	if (time < 10) {
		value = (sin(time / 4.0 - M_PI / 1.75) + 1.0) * 500;
		gl_Position = vec4 (
		round(pos.x * value) / value / ((ratiox > 1.0) ? ratiox : 1.0),
		round(pos.y * value) / value / ((ratioy > 1.0) ? ratioy : 1.0),
		round(pos.z * value) / value, 1.0);
	}
	else {
		gl_Position = vec4 (
		pos.x / ((ratiox > 1.0) ? ratiox : 1.0),
		pos.y / ((ratioy > 1.0) ? ratioy : 1.0),
		pos.z, 1.0);
	}
	vertexPos = vec4 (
		abs(gl_Position.x),
		abs(gl_Position.y),
		abs(gl_Position.z),
		1.0);
	t = time;
}