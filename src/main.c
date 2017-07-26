#include "scop.h"

double		timer(short mod) {
	static double	time = 0.0;
	static short	status = 1;

	if (mod == 0) {
		if (status == 0) {
			glfwSetTime(time);
			status = 1;
		}
		else {
			time = glfwGetTime();
			status = 0;
		}
	}
	else {
		if (status == 0)
			return (time);
		else
			return (glfwGetTime());
	}
	return (0.0);
}

void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		timer(0);
}

GLfloat	*create_mtrx()
{
	GLfloat		*mtrx;
	GLfloat		tha = 1.0f / (tan(90.0 / 2.0 * (M_PI / 180.0f)));
	GLfloat		near = -1.0f;
	GLfloat		far = 1.0f;

	mtrx = (GLfloat *)malloc(sizeof(GLfloat) * 4 * 4);
	mtrx[0 * 0] = tha;
	mtrx[0 * 1] = 0.0;
	mtrx[0 * 2] = 0.0;
	mtrx[0 * 3] = 0.0;
	mtrx[1 * 0] = 0.0;
	mtrx[1 * 1] = tha;
	mtrx[1 * 2] = 0.0;
	mtrx[1 * 3] = 0.0;
	mtrx[2 * 0] = 0.0;
	mtrx[2 * 1] = 0.0;
	mtrx[2 * 2] = -(far + near) / (far - near);
	mtrx[2 * 3] = -(2.0f * far * near) / (far - near);
	mtrx[3 * 0] = 0.0;
	mtrx[3 * 1] = 0.0;
	mtrx[3 * 2] = -1.0f;
	mtrx[3 * 3] = 1.0f;
	return (mtrx);
}

int	 main(int ac, char **av) {
	GLFWwindow*	window;
	GLuint		VAO;
	GLuint		VBO;
	GLuint		EBO;
	GLuint		vShad;
	GLuint		fShad;
	GLuint		shadProg;
	//GLfloat		*mtrx = create_mtrx();
	t_obj_file	obj;
	int width, height;
	(void)ac;

	window = init(1920, 1080, "scop");
	glfwSetKeyCallback(window, key_callback);
	vShad = init_v_shad("./vert.glsl");
	fShad = init_f_shad("./frag.glsl");
	shadProg = init_shad(vShad, fShad);
	obj = parse_obj(av[1]);
	print_info(obj.name);
	print_info(obj.group);
	print_info(ft_itoa(obj.v_len));
	print_info(ft_itoa(obj.i_len));
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * obj.v_len, obj.vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * obj.i_len, obj.indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(sizeof(GLfloat) * 3));
	glBindVertexArray(0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_MULTISAMPLE);
	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shadProg);
		glfwGetWindowSize(window, &width, &height);
		glUniform1i(glGetUniformLocation(shadProg, "mod"), GL_TRUE);
		glUniform1f(glGetUniformLocation(shadProg, "time"), (GLfloat)timer(1));
		glUniform1f(glGetUniformLocation(shadProg, "ratiox"), (float)width / (float)height);
		glUniform1f(glGetUniformLocation(shadProg, "ratioy"), (float)height / (float)width);
	//	glUniformMatrix4fv(glGetUniformLocation(shadProg, "proj"), 1, GL_FALSE, mtrx);
		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, obj.i_len, GL_UNSIGNED_INT, 0);
		glUniform1i(glGetUniformLocation(shadProg, "mod"), GL_FALSE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, obj.i_len, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return (0);
}