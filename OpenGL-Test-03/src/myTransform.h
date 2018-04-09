#ifndef MYTRANSFORM_H
#define MYTRANSFORM_H

#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>

using namespace std;


void changeMatrix(glm::mat4& matrix, int selected) {
	float nowTime = 0, rest = 0;
	switch (selected)
	{
	case 0:
		//  左右平移
		nowTime = (float)glfwGetTime();
		rest = nowTime - (int)nowTime;
		if (rest > 0.5f) {
			matrix = glm::translate(matrix, glm::vec3(-0.001f, 0.0f, 0.0f));
		}
		else {
			matrix = glm::translate(matrix, glm::vec3(0.001f, 0.0f, 0.0f));
		}
		break;
	case 1:
		//  放大
		matrix = glm::scale(matrix, glm::vec3(1.001f, 1.001f, 1.001f));
		break;
	case 2:
		//  缩小
		matrix = glm::scale(matrix, glm::vec3(0.999f, 0.999f, 0.999f));
		break;
	case 3:
		//  旋转
		matrix = glm::rotate(matrix, glm::radians(0.1f), glm::vec3(0.0f, 1.0f, 1.0f));
		break;
	default:
		break;
	}
}

#endif // ! MYTRANSFORM_H
