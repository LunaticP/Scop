#include "scop.h"

void		texture(void)
{
	t_texture		tex;
	GLuint			t;

	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);
	// Set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	// Load and generate the texture
	tex.image = perlin();
	tex.w = 2048;
	tex.h = 2048;
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex.w, tex.h, 0, GL_RGB, GL_UNSIGNED_BYTE, tex.image);
	glGenerateMipmap(GL_TEXTURE_2D);
	ft_memdel(&(tex.image));
	glBindTexture(GL_TEXTURE_2D, 0);
}