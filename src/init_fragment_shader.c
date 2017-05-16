#include "scop.h"

GLuint  init_f_shad(char *file)
{
    const GLchar    *fShadSrc = read_shad(file);
    GLuint          fShad;
    GLint           success;

    fShad = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fShad, 1, &fShadSrc, NULL);
    glCompileShader(fShad);
    glGetShaderiv(fShad, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        ft_putendl("fragment shader : COMPILATION_FAILED");
        exit(-1);
    }
    return (fShad);
}