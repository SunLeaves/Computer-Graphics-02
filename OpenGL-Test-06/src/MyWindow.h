#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <iostream>
#include <glad\glad.h>
#include <glfw\glfw3.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void myProcessInput(GLFWwindow* window);
bool myCreateWindow(GLFWwindow* (&window), string name, int width, int height);


void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, 1000, 1000);
}

void myProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

bool myCreateWindow(GLFWwindow* (&window), string name, int width, int height) {
	//  实例化GLFW窗口
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
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



#endif