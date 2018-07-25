#include "scop.h"

GLuint  init_f_shad(const char *file)
{
	const GLchar	*fShadSrc = read_shad(file);
	GLuint		  fShad;
	GLint		   success;

	fShad = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShad, 1, &fShadSrc, NULL);
	glCompileShader(fShad);
	glGetShaderiv(fShad, GL_COMPILE_STATUS, &success);
	if(!success)
	{
		std::cout << "fragment shader : COMPILATION_FAILED" << std::endl;
		exit(-1);
	}
	return (fShad);
}