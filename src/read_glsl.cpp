#include <fcntl.h>
#include <unistd.h>
#include "scop.h"

GLchar *read_shad(const char *file) {
	std::string shader;
	char	buf[8];
	int	 size;
	int	 fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		std::cout << "Shader File Error" << std::endl;
		exit(-1);
	}
	while ((size = read(fd, buf, 7)) > 0)
	{
		buf[size] = '\0';
		shader = shader + buf;
	}
	close(fd);
	char *output = (char *)malloc(sizeof(char) * shader.size());
	strcpy(output, shader.c_str());
	return ((GLchar *)output);
}
