#include "scop.h"

GLuint  init_shad(GLuint v, GLuint f)
{
	GLuint  shadProg;
	GLint   success;

	shadProg = glCreateProgram();
	glAttachShader(shadProg, v);
	glAttachShader(shadProg, f);
	glLinkProgram(shadProg);
	glGetProgramiv(shadProg, GL_LINK_STATUS, &success);
	if(!success)
	{
		ft_putendl("program shader : LINKING_FAILED");
		exit(-1);
	}
	glDeleteShader(v);
	glDeleteShader(f);
	return (shadProg);
}