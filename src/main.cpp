#include "scop.h"
#include "Object.hpp"
#include "Lights.hpp"

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

int	 main(int ac, char **av) {
	GLFWwindow*	window;
	GLuint		shadProg;
	Light		light(vec3(0.0f), vec3(1.0f, 0.5f, 1.0f));
	int			width;
	int			height;

	window = init(1920, 1080, "scop");
	glfwSetKeyCallback(window, key_callback);
	shadProg = init_shad("/home/lunatic/CODE/Scop/vert.glsl", "/home/lunatic/CODE/Scop/frag.glsl");
	Model		model("/home/lunatic/CODE/Scop/Marvin/marvin4.obj");
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_MULTISAMPLE);
	light.setShader(shadProg);
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetWindowSize(window, &width, &height);
		glUniform1f(glGetUniformLocation(shadProg, "time"), (GLfloat)timer(1));
		glm::mat4 scale(1.0f);
		scale = glm::translate(scale, glm::vec3(0.0f, -0.8f, -3.0f));
		scale = glm::scale(scale, glm::vec3(0.10f));
		glUniformMatrix4fv(glGetUniformLocation(shadProg, "model"), 1, GL_FALSE, glm::value_ptr(scale));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)width/(float)height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(shadProg, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
		model.Draw(shadProg);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}