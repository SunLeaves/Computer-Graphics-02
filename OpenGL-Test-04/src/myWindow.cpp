#include "myWindow.h"

float init_vertices[] = {
	-0.2f, -0.2f, -0.2f, 0.5f, 0.0f, 0.0f,
	0.2f, -0.2f, -0.2f, 0.5f, 0.0f, 0.0f,
	0.2f,  0.2f, -0.2f, 0.5f, 0.0f, 0.0f,
	0.2f,  0.2f, -0.2f, 0.5f, 0.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, 0.5f, 0.0f, 0.0f,
	-0.2f, -0.2f, -0.2f, 0.5f, 0.0f, 0.0f,

	-0.2f, -0.2f,  0.2f, 1.0f, 0.2f, 0.2f,
	0.2f, -0.2f,  0.2f, 1.0f, 0.2f, 0.2f,
	0.2f,  0.2f,  0.2f, 1.0f, 0.2f, 0.2f,
	0.2f,  0.2f,  0.2f, 1.0f, 0.2f, 0.2f,
	-0.2f,  0.2f,  0.2f, 1.0f, 0.2f, 0.2f,
	-0.2f, -0.2f,  0.2f, 1.0f, 0.2f, 0.2f,

	-0.2f,  0.2f,  0.2f, 0.0f, 0.5f, 0.0f,
	-0.2f,  0.2f, -0.2f, 0.0f, 0.5f, 0.0f,
	-0.2f, -0.2f, -0.2f, 0.0f, 0.5f, 0.0f,
	-0.2f, -0.2f, -0.2f, 0.0f, 0.5f, 0.0f,
	-0.2f, -0.2f,  0.2f, 0.0f, 0.5f, 0.0f,
	-0.2f,  0.2f,  0.2f, 0.0f, 0.5f, 0.0f,

	0.2f,  0.2f,  0.2f, 0.0f, 1.0f, 0.5f,
	0.2f,  0.2f, -0.2f, 0.0f, 1.0f, 0.5f,
	0.2f, -0.2f, -0.2f, 0.0f, 1.0f, 0.5f,
	0.2f, -0.2f, -0.2f, 0.0f, 1.0f, 0.5f,
	0.2f, -0.2f,  0.2f, 0.0f, 1.0f, 0.5f,
	0.2f,  0.2f,  0.2f, 0.0f, 1.0f, 0.5f,

	-0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 1.0f,
	0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 1.0f,
	0.2f, -0.2f,  0.2f, 1.0f, 0.0f, 1.0f,
	0.2f, -0.2f,  0.2f, 1.0f, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 1.0f, 0.0f, 1.0f,
	-0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 1.0f,

	-0.2f,  0.2f, -0.2f, 1.0f, 1.0f, 1.0f,
	0.2f,  0.2f, -0.2f, 1.0f, 1.0f, 1.0f,
	0.2f,  0.2f,  0.2f, 1.0f, 1.0f, 1.0f,
	0.2f,  0.2f,  0.2f, 1.0f, 1.0f, 1.0f,
	-0.2f,  0.2f,  0.2f, 1.0f, 1.0f, 1.0f,
	-0.2f,  0.2f, -0.2f, 1.0f, 1.0f, 1.0f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, 1000, 1000);
}

void myProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

bool myCreateWindow(GLFWwindow* (&window), int width, int height) {
	//  实例化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "HW5", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create a window." << endl;
		return false;
	}

	//  窗口绑定到当前线程
	glfwMakeContextCurrent(window);

	//  使用glad
	if (!gladLoadGLLoader(((GLADloadproc)glfwGetProcAddress))) {
		cout << "Failed to initialize GLAD." << endl;
		return false;
	}

	//  设置视口
	glViewport(0, 0, width, height);

	//  为窗口window注册回调函数
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return true;
}

void getPoints(float(&vertices)[36][6]) {
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 6; j++) {
			vertices[i][j] = init_vertices[i * 6 + j];
		}
	}
}