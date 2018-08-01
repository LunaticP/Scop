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

GLuint  init_shad(std::string vertexShaderPath, std::string fragementShaderPath)
{
	GLuint	shadProg;
	GLuint	vShad;
	GLuint	fShad;
	GLint	success;

	shadProg = glCreateProgram();
	vShad = init_v_shad(vertexShaderPath.c_str());
	fShad = init_f_shad(fragementShaderPath.c_str());
	glAttachShader(shadProg, vShad);
	glAttachShader(shadProg, fShad);
	glLinkProgram(shadProg);
	glGetProgramiv(shadProg, GL_LINK_STATUS, &success);
	if(!success)
	{
		std::cout << "program shader : LINKING_FAILED" << std::endl;
		exit(-1);
	}
	glDeleteShader(vShad);
	glDeleteShader(fShad);
	return (shadProg);
}