#include "scop.h"

double		timer(short mod) {
	static double	time = 12.0;
	static short	status = 0;

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
	int width, height;
	(void)ac;

	window = init(1920, 1080, "scop");
	glfwSetKeyCallback(window, key_callback);
	vShad = init_v_shad("/home/lunatic/CODE/Scop/vert.glsl");
	fShad = init_f_shad("/home/lunatic/CODE/Scop/frag.glsl");
	shadProg = init_shad(vShad, fShad);
	Model model("/home/lunatic/CODE/Scop/nanosuit/nanosuit.obj");
	GLfloat vertices[] = {
			// positions          // colors           // texture coords
			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
	};
	GLuint indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

//	glLineWidth(0.3f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_MULTISAMPLE);

	while(!glfwWindowShouldClose(window)) {
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glUseProgram(shadProg);
		glfwGetWindowSize(window, &width, &height);
		glUniform1f(glGetUniformLocation(shadProg, "time"), (GLfloat)timer(1));
		glUniform1f(glGetUniformLocation(shadProg, "ratiox"), (float)width / (float)height);
		glUniform1f(glGetUniformLocation(shadProg, "ratioy"), (float)height / (float)width);
//		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
//		glUniformMatrix4fv(glGetUniformLocation(shadProg, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
		glm::mat4 scale(1.0f);
		scale = glm::translate(scale, glm::vec3(0.0f, -2.2f, 0.0f)); // translate it down so it's at the center of the scene
		scale = glm::scale(scale, glm::vec3(0.20f, 0.20f, 0.20f));	// it's a bit too big for our scene, so scale it down
		glUniformMatrix4fv(glGetUniformLocation(shadProg, "model"), 1, GL_FALSE, glm::value_ptr(scale));
		glUniform1i(glGetUniformLocation(shadProg, "mod"), GL_TRUE);
		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		model.Draw(shadProg);
		glUniform1i(glGetUniformLocation(shadProg, "mod"), GL_FALSE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		model.Draw(shadProg);
		glUniform1i(glGetUniformLocation(shadProg, "mod"), GL_TRUE);
		glBindVertexArray(VAO);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glDrawElements(GL_TRIANGLES, 31, GL_UNSIGNED_INT, 0);
		glUniform1i(glGetUniformLocation(shadProg, "mod"), GL_FALSE);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, 5, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return (0);
}