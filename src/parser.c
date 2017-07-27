#include "scop.h"

void		add_vertices(char *line, GLfloat *v, GLuint *size)
{
	v[*size] = (GLfloat)ft_atof(line);
	line = ft_strchr(line, ' ') + 1;
	v[*size + 1] = (GLfloat)ft_atof(line);
	line = ft_strchr(line, ' ');
	v[*size + 2] = (GLfloat)ft_atof(line);
	*size += 5;
}

void 		add_indices(char *line, GLuint *i, GLuint *size)
{
	i[*size] = (GLuint)ft_atoi(line) - 1;
	line = ft_strchr(line, '/') + 1;
	i[*size + 3] = (GLuint)ft_atoi(line) - 1;
	line = ft_strchr(line, ' ') + 1;
	i[*size + 1] = (GLuint)ft_atoi(line) - 1;
	line = ft_strchr(line, '/') + 1;
	i[*size + 4] = (GLuint)ft_atoi(line) - 1;
	line = ft_strchr(line, ' ') + 1;
	i[*size + 2] = (GLuint)ft_atoi(line) - 1;
	line = ft_strchr(line, '/') + 1;
	i[*size + 5] = (GLuint)ft_atoi(line) - 1;
	*size += 6;
}

void 		add_uv(char *line, GLfloat *t, GLuint *size)
{
	t[*size] = (GLfloat)ft_atof(line);
	line = ft_strchr(line, ' ') + 1;
	t[*size + 1] = (GLfloat)ft_atof(line);
	*size += 5;
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
	if (!ft_strncmp("vt ", line, 3))
		add_uv(&line[3], obj->vertices, &(obj->t_len));
}

void		init_obj(t_obj_file *obj, char *file) {
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
			obj->v_len += 5;
		if (!ft_strncmp("f ", line, 2))
			obj->i_len += 6;
		ft_memdel((void**)&line);
	}
	ft_memdel((void**)&line);
	close(fd);
}

t_obj_file	parse_obj(char *file) {
	t_obj_file obj;
	char *line;
	int fd;

	init_obj(&obj, file);
	obj.vertices = (GLfloat *)ft_memalloc(sizeof(GLfloat) * obj.v_len);
	obj.indices = (GLuint *)ft_memalloc(sizeof(GLuint) * obj.i_len);
//	obj.t_ind = (GLuint *)ft_memalloc(sizeof(GLuint) * obj.i_len);
	obj.name = "test";
	obj.group = "test";
	obj.v_len = 0;
	obj.i_len = 0;
	obj.t_len = 3;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		parse_line(line, &obj);
		ft_memdel((void**)&line);
	}
	parse_line(line, &obj);
	ft_memdel((void**)&line);
	close(fd);
	for (int i = 0; i < obj.v_len; i++) {
		if (obj.vertices[i] < 0.0f)
			printf("%.1f\t", obj.vertices[i]);
		else
			printf(" %.1f\t", obj.vertices[i]);
		if (i % 5 == 0)
			ft_putendl("");
		fflush(0);
	}
	for (int i = 0; i < obj.i_len; i++) {
		printf("%d\t", obj.indices[i]);
		if (i % 6 == 0)
			ft_putendl("");
		fflush(0);
	}
	ft_putendl("");
	return (obj);
}