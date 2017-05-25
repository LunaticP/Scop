#version 330 core

layout (location = 0) in vec3 position;

out	 vec4	vertexColor;
out	 vec4	vertexPos;
out  float  t;
uniform float   time;
uniform float   ratiox;
uniform float   ratioy;

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

    pos = vec4(position / 15.0, 1.0);
    pos.y -= 0.3;
	vertexColor = pos;

    pos = vec4(
    pos.x * cos(time) + pos.z * sin(time),
    pos.y,
    pos.x * -sin(time) + pos.z * cos(time),
    1.0);

    pos = vec4(
    pos.x,
    pos.y * cos(0.4) - pos.z * sin(0.4),
    pos.y * sin(0.4) + pos.z * cos(0.4),
    1.0);

	gl_Position = vec4 (
	pos.x / ((ratiox > 1.0) ? ratiox : 1.0),
	pos.y / ((ratioy > 1.0) ? ratioy : 1.0),
	pos.z, 1.0);

	vertexPos = vec4 (gl_Position.x, gl_Position.y, gl_Position.z, 1.0);
	t = time;
}