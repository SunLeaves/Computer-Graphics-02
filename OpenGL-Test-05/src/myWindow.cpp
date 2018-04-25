#include "myWindow.h"

float init_obj_vertices[] = {
	//  �����
	-0.2f, -0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	0.2f, -0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	0.2f,  0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	0.2f,  0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	-0.2f,  0.2f, -0.2f, 0.0f, 0.0f, -1.0f,
	-0.2f, -0.2f, -0.2f, 0.0f, 0.0f, -1.0f,

	//  ǰ����
	-0.2f, -0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	0.2f, -0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	0.2f,  0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	0.2f,  0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	-0.2f,  0.2f,  0.2f, 0.0f, 0.0f, 1.0f,
	-0.2f, -0.2f,  0.2f, 0.0f, 0.0f, 1.0f,

	//  �����
	-0.2f,  0.2f,  0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f,  0.2f, -0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f, -0.2f, -0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f, -0.2f, -0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f, -0.2f,  0.2f, -1.0f, 0.0f, 0.0f,
	-0.2f,  0.2f,  0.2f, -1.0f, 0.0f, 0.0f,

	//  �ұ���
	0.2f,  0.2f,  0.2f, 1.0f, 0.0f, 0.0f,
	0.2f,  0.2f, -0.2f, 1.0f, 0.0f, 0.0f,
	0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 0.0f,
	0.2f, -0.2f, -0.2f, 1.0f, 0.0f, 0.0f,
	0.2f, -0.2f,  0.2f, 1.0f, 0.0f, 0.0f,
	0.2f,  0.2f,  0.2f, 1.0f, 0.0f, 0.0f,

	//  �����
	-0.2f, -0.2f, -0.2f, 0.0f, -1.0f,  0.0f,
	0.2f, -0.2f, -0.2f, 0.0f, -1.0f,  0.0f,
	0.2f, -0.2f,  0.2f, 0.0f, -1.0f,  0.0f,
	0.2f, -0.2f,  0.2f, 0.0f, -1.0f,  0.0f,
	-0.2f, -0.2f,  0.2f, 0.0f, -1.0f,  0.0f,
	-0.2f, -0.2f, -0.2f, 0.0f, -1.0f,  0.0f,

	//  ǰ����
	-0.2f,  0.2f, -0.2f, 0.0f, 1.0f,  0.0f,
	0.2f,  0.2f, -0.2f, 0.0f, 1.0f,  0.0f,
	0.2f,  0.2f,  0.2f, 0.0f, 1.0f,  0.0f,
	0.2f,  0.2f,  0.2f, 0.0f, 1.0f,  0.0f,
	-0.2f,  0.2f,  0.2f, 0.0f, 1.0f,  0.0f,
	-0.2f,  0.2f, -0.2f, 0.0f, 1.0f,  0.0f
};

float init_light_vertices[36][3] = {
	-0.05f, -0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	0.05f,  0.05f, -0.05f,
	0.05f,  0.05f, -0.05f,
	-0.05f,  0.05f, -0.05f,
	-0.05f, -0.05f, -0.05f,

	-0.05f, -0.05f,  0.05f,
	0.05f, -0.05f,  0.05f,
	0.05f,  0.05f,  0.05f,
	0.05f,  0.05f,  0.05f,
	-0.05f,  0.05f,  0.05f,
	-0.05f, -0.05f,  0.05f,

	-0.05f,  0.05f,  0.05f,
	-0.05f,  0.05f, -0.05f,
	-0.05f, -0.05f, -0.05f,
	-0.05f, -0.05f, -0.05f,
	-0.05f, -0.05f,  0.05f,
	-0.05f,  0.05f,  0.05f,

	0.05f,  0.05f,  0.05f,
	0.05f,  0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	0.05f, -0.05f,  0.05f,
	0.05f,  0.05f,  0.05f,

	-0.05f, -0.05f, -0.05f,
	0.05f, -0.05f, -0.05f,
	0.05f, -0.05f,  0.05f,
	0.05f, -0.05f,  0.05f,
	-0.05f, -0.05f,  0.05f,
	-0.05f, -0.05f, -0.05f,

	-0.05f,  0.05f, -0.05f,
	0.05f,  0.05f, -0.05f,
	0.05f,  0.05f,  0.05f,
	0.05f,  0.05f,  0.05f,
	-0.05f,  0.05f,  0.05f,
	-0.05f,  0.05f, -0.05f
};

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, 1000, 1000);
}

void myProcessInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

bool myCreateWindow(GLFWwindow* (&window), int width, int height) {
	//  ʵ����GLFW����
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	window = glfwCreateWindow(width, height, "HW5", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to create a window." << endl;
		return false;
	}

	//  ���ڰ󶨵���ǰ�߳�
	glfwMakeContextCurrent(window);

	//  ʹ��glad
	if (!gladLoadGLLoader(((GLADloadproc)glfwGetProcAddress))) {
		cout << "Failed to initialize GLAD." << endl;
		return false;
	}

	//  �����ӿ�
	glViewport(0, 0, width, height);

	//  Ϊ����windowע��ص�����
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	return true;
}

void getObjVertices(float(&vertices)[36][6]) {
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 6; j++) {
			vertices[i][j] = init_obj_vertices[i * 6 + j];
		}
	}
}

void getLightVertices(float(&vertices)[36][3]) {
	for (int i = 0; i < 36; i++) {
		for (int j = 0; j < 3; j++) {
			vertices[i][j] = init_light_vertices[i][j];
		}
	}
}