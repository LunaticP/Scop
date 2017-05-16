#ifndef SCOP_SCOP_H
# define SCOP_SCOP_H

# define SCOP_SCOP_H
# define GLEW_STATIC

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include "libft.h"

GLFWwindow      *init(int x, int y, char *name);
GLuint          init_v_shad(char *file);
GLuint          init_f_shad(char *file);
GLuint          init_shad(GLuint v, GLuint f);
GLchar          *read_shad(char *file);
#endif