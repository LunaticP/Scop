#include "scop.h"

GLuint  init_v_shad(const char *file)
{
	const GLchar	*vShadSrc = read_shad(file);
	GLuint		  vShad;
	GLint		   success;

	vShad = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShad, 1, &vShadSrc, NULL);
	glCompileShader(vShad);
	glGetShaderiv(vShad, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		std::cout << "vertex shader : COMPILATION_FAILED" << std::endl;
		exit(-1);
	}
	return (vShad);
}