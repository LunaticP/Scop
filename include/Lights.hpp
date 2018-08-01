#include "scop.h"
using namespace std;
using namespace glm;

#ifndef LIGHTS_HPP
#define LIGHTS_HPP

class Light {
public:
    vec3    position;
    vec3    color;
    float   intensity;

    Light(vec3 pos, vec3 col) {
        this->position = pos;
        this->color = col;
    }
    void setPosition(vec3 pos) {
        this->position = pos;
    }
    vec3 getPosition() {
        return this->position;
    }
    void setColor(vec3 col) {
        this->color = col;
    }
    vec3 getColor() {
        return this->color;
    }
    void setShader(GLuint shader) {
        glUniform3f(glGetUniformLocation(shader, "light.Position"), this->position.x, this->position.y, this->position.z);
//        glUniform3f(glGetUniformLocation(shader, "light.Color"), this->color.r, this->color.g, this->color.b);
        glUniform3f(glGetUniformLocation(shader, "light.Color"), 1.0f, 0.5f, 1.0f);
        glUniform1f(glGetUniformLocation(shader, "light.Intensity"), intensity);
    }
};

#endif
