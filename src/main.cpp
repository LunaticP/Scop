#include "scop.h"
#ifndef STB_IMAGE_IMPLEMENTATION
# define STB_IMAGE_IMPLEMENTATION
# include "stb_image.h"
#endif

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
	GLuint		VAO;
	GLuint		VBO;
	GLuint		EBO;
	GLuint		vShad;
	GLuint		fShad;
	GLuint		shadProg;
	int width, height, texWidth, texHeight, texChannels;
	(void)ac;

	window = init(1920, 1080, "scop");
	glfwSetKeyCallback(window, key_callback);
	vShad = init_v_shad("/home/lunatic/CODE/Scop/vert.glsl");
	fShad = init_f_shad("/home/lunatic/CODE/Scop/frag.glsl");
	shadProg = init_shad(vShad, fShad);
	Model model("/home/lunatic/CODE/Scop/nanosuit/nanosuit.obj");
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	stbi_set_flip_vertically_on_load(true);
	unsigned char *data = stbi_load("/home/lunatic/CODE/Scop/Marvin/textest.jpg", &texWidth, &texHeight, &texChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "image fail" << std::endl;
	}
	stbi_image_free(data);
//	GLfloat vertices[] = {
//			// positions          // colors           // texture coords
//			0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
//			0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
//			-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
//			-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left
//	};
//	GLuint indices[] = {
//			0, 1, 2, // first triangle
//			0, 2, 3  // second triangle
//	};
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 32, vertices, GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 6, indices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//	glEnableVertexAttribArray(1);
//
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//	glEnableVertexAttribArray(2);

//	glLineWidth(0.3f);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_MULTISAMPLE);
	glUniform1i(glGetUniformLocation(shadProg, "catTex"), 0);
	while(!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwGetWindowSize(window, &width, &height);
		glUniform1f(glGetUniformLocation(shadProg, "time"), (GLfloat)timer(1));
		glm::mat4 scale(1.0f);
		scale = glm::translate(scale, glm::vec3(0.0f, -0.8f, 0.0f));
		scale = glm::scale(scale, glm::vec3(0.10f));
//		scale = glm::rotate(scale, AI_MATH_HALF_PI_F, (glm::vec3(1.0f, 0.0f, 0.0f)));
		glUniformMatrix4fv(glGetUniformLocation(shadProg, "model"), 1, GL_FALSE, glm::value_ptr(scale));
		glBindTexture(GL_TEXTURE_2D, texture);
		model.Draw(shadProg);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return (0);
}