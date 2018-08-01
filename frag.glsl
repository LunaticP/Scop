#version 330 core

struct Material {
    vec3    ambient;
    vec3    diffuse;
    vec3    specular;
    float   shininess;
};

struct Light {
    vec3    Position;
    vec3    Color;
    float   Intensity;
};

in	vec3	vertexNormal;
in  vec2    vertexTex;
out	vec4	color;

uniform     sampler2D   catTex;
uniform     Material    material;
uniform     Light       light;

void main()
{
    color = vec4(light.Color, 1.0);
//	color = texture(catTex,  vertexTex) * vec4(abs(vertexNormal.x), abs(vertexNormal.y), abs(vertexNormal.z), 1.0f);
}