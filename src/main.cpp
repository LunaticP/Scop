//#include "scop.h"
//#include "Object.hpp"
//#include "Lights.hpp"
//#include <stdio.h>
//#include <irrKlang.h>
//#include <conio.h>
//using namespace irrklang;
//
//double		timer(short mod) {
//	static double	time = 12.0;
//	static short	status = 0;
//
//	if (mod == 0) {
//		if (status == 0) {
//			glfwSetTime(time);
//			status = 1;
//		}
//		else {
//			time = glfwGetTime();
//			status = 0;
//		}
//	}
//	else {
//		if (status == 0)
//			return (time);
//		else
//			return (glfwGetTime());
//	}
//	return (0.0);
//}
//
//void	key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
//	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, GL_TRUE);
//	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
//		timer(0);
//}
//
//int	 main(int ac, char **av) {
//	GLFWwindow*	window;
//	GLuint		shadProg;
//	Light		light(vec3(0.0f), vec3(1.0f, 0.5f, 1.0f));
//	int			width;
//	int			height;
//	ISoundEngine* engine = createIrrKlangDevice();
//
//	if (!engine) {
//		std::cout << "Create sound engine error" << std::endl;
//		return 0;
//	}
//	if (!engine->loadPlugins("/home/lunatic/CODE/Scop/IrrKlang/bin/ikpMP3.so")) {
//		std::cout << "MP3 plugin failed" << std::endl;
//	} else {
//		std::cout << "MP3 plugin loaded" << std::endl;
//	}
//	ISound* playback = engine->play2D("/home/lunatic/CODE/Scop/ninur.wav", true, false, true);
//
//	window = init(1920, 1080, "scop");
//	glfwSetKeyCallback(window, key_callback);
//	shadProg = init_shad("/home/lunatic/CODE/Scop/vert.glsl", "/home/lunatic/CODE/Scop/frag.glsl");
//	Model		model("/home/lunatic/CODE/Scop/Marvin/marvin4.obj");
//	glEnable(GL_DEPTH_TEST);
//	glEnable(GL_MULTISAMPLE);
//	light.setShader(shadProg);
//	while(!glfwWindowShouldClose(window)) {
//		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		playback->setVolume(static_cast<ik_f32>((sin(timer(1)) + 1.0f) / 2.0f));
//		float pos = playback->getPlayPosition();
//		float val = pos / playback->getPlayLength();
//		glfwGetWindowSize(window, &width, &height);
//		glUniform1f(glGetUniformLocation(shadProg, "time"), (GLfloat)timer(1));
//		glm::mat4 scale(1.0f);
//		scale = glm::translate(scale, glm::vec3(0.0f, -0.8f, -3.0f));
//		scale = glm::scale(scale, glm::vec3(0.10f));
//		glUniformMatrix4fv(glGetUniformLocation(shadProg, "model"), 1, GL_FALSE, glm::value_ptr(scale));
//		glm::mat4 projection = glm::perspective(glm::radians(val * 45.0f), (float)width/(float)height, 0.1f, 100.0f);
//		glUniformMatrix4fv(glGetUniformLocation(shadProg, "proj"), 1, GL_FALSE, glm::value_ptr(projection));
//		model.Draw(shadProg);
//		glfwSwapBuffers(window);
//		glfwPollEvents();
//	}
//	glfwTerminate();
//	return (0);
//}

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include <pulse/simple.h>
#include <pulse/error.h>
#include <pulse/gccmacro.h>
#include <iostream>

#define BUFSIZE 1024
/*
#define BYTE_8_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_16_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_32_PATTERN "%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY8(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0')
#define BYTE_TO_BINARY16(byte)  \
  (byte & 0x8000 ? '1' : '0'), \
  (byte & 0x4000 ? '1' : '0'), \
  (byte & 0x2000 ? '1' : '0'), \
  (byte & 0x1000 ? '1' : '0'), \
  (byte & 0x0800 ? '1' : '0'), \
  (byte & 0x0400 ? '1' : '0'), \
  (byte & 0x0200 ? '1' : '0'), \
  (byte & 0x0100 ? '1' : '0'), \
  (byte & 0x0080 ? '1' : '0'), \
  (byte & 0x0040 ? '1' : '0'), \
  (byte & 0x0020 ? '1' : '0'), \
  (byte & 0x0010 ? '1' : '0'), \
  (byte & 0x0008 ? '1' : '0'), \
  (byte & 0x0004 ? '1' : '0'), \
  (byte & 0x0002 ? '1' : '0'), \
  (byte & 0x0001 ? '1' : '0')
#define BYTE_TO_BINARY32(byte)  \
  (byte & 0x80000000 ? '1' : '0'), \
  (byte & 0x40000000 ? '1' : '0'), \
  (byte & 0x20000000 ? '1' : '0'), \
  (byte & 0x10000000 ? '1' : '0'), \
  (byte & 0x08000000 ? '1' : '0'), \
  (byte & 0x04000000 ? '1' : '0'), \
  (byte & 0x02000000 ? '1' : '0'), \
  (byte & 0x01000000 ? '1' : '0'), \
  (byte & 0x00800000 ? '1' : '0'), \
  (byte & 0x00400000 ? '1' : '0'), \
  (byte & 0x00200000 ? '1' : '0'), \
  (byte & 0x00100000 ? '1' : '0'), \
  (byte & 0x00080000 ? '1' : '0'), \
  (byte & 0x00040000 ? '1' : '0'), \
  (byte & 0x00020000 ? '1' : '0'), \
  (byte & 0x00010000 ? '1' : '0'), \
  (byte & 0x00008000 ? '1' : '0'), \
  (byte & 0x00004000 ? '1' : '0'), \
  (byte & 0x00002000 ? '1' : '0'), \
  (byte & 0x00001000 ? '1' : '0'), \
  (byte & 0x00000800 ? '1' : '0'), \
  (byte & 0x00000400 ? '1' : '0'), \
  (byte & 0x00000200 ? '1' : '0'), \
  (byte & 0x00000100 ? '1' : '0'), \
  (byte & 0x00000080 ? '1' : '0'), \
  (byte & 0x00000040 ? '1' : '0'), \
  (byte & 0x00000020 ? '1' : '0'), \
  (byte & 0x00000010 ? '1' : '0'), \
  (byte & 0x00000008 ? '1' : '0'), \
  (byte & 0x00000004 ? '1' : '0'), \
  (byte & 0x00000002 ? '1' : '0'), \
  (byte & 0x00000001 ? '1' : '0')
*/
pa_sample_spec  parseWaveHeader(uint8_t header[44]) {
    uint16_t        channels = (header[23] << 8) + header[22];
    uint16_t        format = (header[35] << 8) + header[34];
    uint32_t        sampleRate = (header[27] << 24) + (header[26] << 16) + (header[25] << 8) + header[24];

    pa_sample_spec out = {
            .format = PA_SAMPLE_S16LE,
            .rate = sampleRate,
            .channels = (uint8_t)channels
    };
    return out;
}

int main(int argc, char **argv) {
    pa_simple   *s = NULL;
    uint8_t     waveHeader[44];
    ssize_t     r;
    int         ret = 1;
    int         error;

    if (argc > 1) {
        int fd;

        if ((fd = open(argv[1], O_RDONLY)) < 0) {
            fprintf(stderr, __FILE__": open() failed: %s\n", strerror(errno));
            goto finish;
        }

        if (read(fd, waveHeader, sizeof(waveHeader)) < 0) {
            fprintf(stderr, __FILE__": read() failed: %s\n", strerror(errno));
            goto finish;
        }
        std::cout << "header read" << std::endl;
        static const pa_sample_spec ss = parseWaveHeader(waveHeader);

        if (!(s = pa_simple_new(NULL, argv[0], PA_STREAM_PLAYBACK, NULL, "playback", &ss, NULL, NULL, &error))) {
            fprintf(stderr, __FILE__": pa_simple_new() failed: %s\n", pa_strerror(error));
            goto finish;
        }
        for (;;) {
            uint8_t buf[BUFSIZE];
#if 0
            pa_usec_t latency;

        if ((latency = pa_simple_get_latency(s, &error)) == (pa_usec_t) -1) {
            fprintf(stderr, __FILE__": pa_simple_get_latency() failed: %s\n", pa_strerror(error));
            goto finish;
        }

        fprintf(stderr, "%0.0f usec    \r", (float)latency);
#endif
            if ((r = read(fd, buf, sizeof(buf))) <= 0) {
                if (r == 0) /* EOF */
                    break;
                fprintf(stderr, __FILE__": read() failed: %s\n", strerror(errno));
                goto finish;
            }
            if (pa_simple_write(s, buf, (size_t) r, &error) < 0) {
                fprintf(stderr, __FILE__": pa_simple_write() failed: %s\n", pa_strerror(error));
                goto finish;
            }
        }

        /* Make sure that every single sample was played */
        if (pa_simple_drain(s, &error) < 0) {
            fprintf(stderr, __FILE__": pa_simple_drain() failed: %s\n", pa_strerror(error));
            goto finish;
        }

        ret = 0;
        close(fd);
    }

    finish:

    if (s)
        pa_simple_free(s);

    return ret;
}
