#ifndef SCOP_H
# define SCOP_H

# ifndef GLEW_STATIC
#  define GLEW_STATIC
# endif

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"
#include <stdio.h>
#include <Object.hpp>

GLFWwindow	*init(int x, int y, const char *name);
GLuint		init_v_shad(const char *file);
GLuint		init_f_shad(const char *file);
GLuint		init_shad(GLuint v, GLuint f);
GLchar		*read_shad(const char *file);
int			*perlin(void);

#endif
