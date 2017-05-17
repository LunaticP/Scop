#include <fcntl.h>
#include <unistd.h>
#include "scop.h"

GLchar  *read_shad(char *file)
{
	char	*shader;
	char	buf[8];
	int	 size;
	int	 fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putendl("file error");
		exit(-1);
	}
	shader = ft_strnew(0);
	while ((size = read(fd, buf, 7)) > 0)
	{
		buf[size] = '\0';
		shader = ft_freejoin(shader, buf);
	}
	close(fd);
	return (shader);
}