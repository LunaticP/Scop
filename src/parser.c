#include "scop.h"

void		add_vertices(char *line, GLfloat *v, GLuint *size)
{
	v[*size] = (GLfloat)ft_atof(line);
	line = ft_strchr(line, ' ') + 1;
	v[*size + 1] = (GLfloat)ft_atof(line);
	line = ft_strchr(line, ' ');
	v[*size + 2] = (GLfloat)ft_atof(line);
	*size += 3;
}

void 		add_indices(char *line, GLuint *i, GLuint *size)
{
	i[*size] = (GLuint)ft_atoi(line) - 1;
	line = ft_strchr(line, ' ') + 1;
	i[*size + 1] = (GLuint)ft_atoi(line) - 1;
	line = ft_strchr(line, ' ');
	i[*size + 2] = (GLuint)ft_atoi(line) - 1;
	*size += 3;
}

void		parse_line(char *line, t_obj_file *obj)
{
	if (!ft_strncmp("o ", line, 2))
		obj->name = ft_strdup(&line[2]);
	if (!ft_strncmp("g ", line, 2))
		obj->group = ft_strdup(&line[2]);
	if (!ft_strncmp("v ", line, 2))
		add_vertices(&line[2], obj->vertices, &(obj->v_len));
	if (!ft_strncmp("f ", line, 2))
		add_indices(&line[2], obj->indices, &(obj->i_len));
}

void		init_obj(t_obj_file *obj, char *file)
{
	char	*line;
	int 	fd;

	fd = open(file, O_RDONLY);
	if (fd < 1)
	{
		print_info("file error");
		exit(-1);
	}
	while (get_next_line(fd, &line))
	{
		if (!ft_strncmp("v ", line, 2))
			obj->v_len += 3;
		if (!ft_strncmp("f ", line, 2))
			obj->i_len += 3;
		ft_memdel((void**)&line);
	}
	ft_memdel((void**)&line);
	close(fd);
}

t_obj_file	parse_obj(char *file)
{
	t_obj_file obj;
	char *line;
	int fd;

	init_obj(&obj, file);
	obj.vertices = (GLfloat *)ft_memalloc(sizeof(GLfloat) * obj.v_len);
	obj.indices = (GLuint *)ft_memalloc(sizeof(GLuint) * obj.i_len);
	obj.name = "test";
	obj.group = "test";
	obj.v_len = 0;
	obj.i_len = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		parse_line(line, &obj);
		ft_memdel((void**)&line);
	}
	parse_line(line, &obj);
	ft_memdel((void**)&line);
	close(fd);
	return (obj);
}