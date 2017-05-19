#include "scop.h"
#include <stdio.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int	 main(int ac, char **av)
{
	GLFWwindow*	window;
	GLuint	  	VAO;
	GLuint	  	VBO;
	GLuint	  	EBO;
	GLuint	  	vShad;
	GLuint	  	fShad;
	GLuint	  	shadProg;
	t_obj_file	obj;
	int width, height;
	(void)ac;

	obj = parse_obj(av[1]);
	print_info(obj.name);
	print_info(obj.group);
	print_info(ft_itoa(obj.v_len));
	print_info(ft_itoa(obj.i_len));
	window = init(1280, 720, "scop");
	glfwSetKeyCallback(window, key_callback);
	vShad = init_v_shad("./vert");
	fShad = init_f_shad("./frag");
	shadProg = init_shad(vShad, fShad);
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * obj.v_len, obj.vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * obj.i_len, obj.indices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shadProg);
		glfwGetWindowSize(window, &width, &height);
		glUniform1f(glGetUniformLocation(shadProg, "time"), glfwGetTime());
		glUniform1f(glGetUniformLocation(shadProg, "ratiox"), (float)width / (float)height);
		glUniform1f(glGetUniformLocation(shadProg, "ratioy"), (float)height / (float)width);
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, obj.i_len, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return (0);
}