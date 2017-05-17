#ifndef SCOP_H
# define SCOP_H

# ifndef GLEW_STATIC
#  define GLEW_STATIC
# endif

# include <glew.h>
# include <glfw3.h>
# include <stdlib.h>
# include <math.h>
# include "libft.h"

typedef struct	s_obj_file
{
	GLfloat		*vertices;
	GLuint		*indices;
}				t_obj_file;

GLFWwindow	*init(int x, int y, char *name);
GLuint		init_v_shad(char *file);
GLuint		init_f_shad(char *file);
GLuint		init_shad(GLuint v, GLuint f);
GLchar		*read_shad(char *file);
t_obj_file	parse_obj(char *obj);

#endif