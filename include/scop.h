#ifndef SCOP_H
# define SCOP_H

# ifndef GLEW_STATIC
#  define GLEW_STATIC
# endif

# include <GL/glew.h>
# include <GLFW/glfw3.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include <stdio.h>

typedef	struct		s_texture
{
	unsigned char	*image;
	int				w;
	int				h;
}					t_texture;

typedef struct	s_obj_file
{
	char 		*name;
	char 		*group;
	GLfloat		*vertices;
	GLuint		*indices;
	GLuint		*t_ind;
	GLuint		v_len;
	GLuint		t_len;
	GLuint		i_len;
}				t_obj_file;

GLFWwindow	*init(int x, int y, char *name);
GLuint		init_v_shad(char *file);
GLuint		init_f_shad(char *file);
GLuint		init_shad(GLuint v, GLuint f);
GLchar		*read_shad(char *file);
t_obj_file	parse_obj(char *obj);
int			*perlin(void);

#endif
