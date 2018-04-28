#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw_gl3.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>
#include <string>

#include "MyWindow.h"
#include "Shader.h"
#include "MyVertices.h"

using namespace std;

int main() {
	GLFWwindow* window = NULL;

	//  着色器路径
	string objVertexShaderPath = "";
	string objFragShaderPath = "";

	//  VBO、VAO
	unsigned int objVAO = 0;
	unsigned int objVBO = 0;
	unsigned int planeVAO = 0;
	unsigned int planeVBO = 0;

	//  矩阵
	glm::mat4 identity(1);
	glm::mat4 objModel(1);
	glm::mat4 planeModel(1);
	glm::mat4 lightModel(1);
	glm::mat4 view(1);
	glm::mat4 projection(1);

	//  视角，物体中心，上向量
	glm::vec3 viewPos = { 2.0f, 2.0f, 2.0f };
	glm::vec3 objCenter = { 0.0f, 0.0f, 0.0f };
	glm::vec3 upVec = { 0.0f, 1.0f, 0.0f };

	//  光源位置、颜色、（立方体）顶点位置信息
	glm::vec3 lightPos = { -1.0f, 1.0f, -1.0f };
	glm::vec3 lightColor = { 1.0f, 1.0f, 1.0f };
	//  float lightVertices[36][3] = { 0 };

	//  物体、平面的颜色、顶点位置信息
	glm::vec3 objColor = { 0.1f, 0.1f, 0.5f };
	float objVertices[36][6] = { 0 };
	float planeVertices[36][6] = { 0 };

	//  背景颜色
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	/*-------------------------初始化---------------------*/

	//  初始化顶点矩阵
	setObjVertices(objVertices);
	setPlaneVertices(planeVertices);

}