#include "scop.h"

t_obj_file	parse_obj(char *file) {
	t_obj_file obj;

	obj.vertices = {
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   // bottom right
			-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   // bottom left
			0.0f,  0.5f, 0.0f,
	obj.indices = ;
	obj.name = "test";
	obj.group = "test";
	obj.v_len = 0;
	obj.i_len = 0;
	return (obj);
}