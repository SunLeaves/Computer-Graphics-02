#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <iostream>
#include <glad\glad.h>
#include <GLFW\glfw3.h>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void myProcessInput(GLFWwindow* window);
bool myCreateWindow(GLFWwindow* (&window), int width, int height);


#endif
