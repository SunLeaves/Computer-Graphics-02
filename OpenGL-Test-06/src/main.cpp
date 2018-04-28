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

	//  ��ɫ��·��
	string objVertexShaderPath = "";
	string objFragShaderPath = "";

	//  VBO��VAO
	unsigned int objVAO = 0;
	unsigned int objVBO = 0;
	unsigned int planeVAO = 0;
	unsigned int planeVBO = 0;

	//  ����
	glm::mat4 identity(1);
	glm::mat4 objModel(1);
	glm::mat4 planeModel(1);
	glm::mat4 lightModel(1);
	glm::mat4 view(1);
	glm::mat4 projection(1);

	//  �ӽǣ��������ģ�������
	glm::vec3 viewPos = { 2.0f, 2.0f, 2.0f };
	glm::vec3 objCenter = { 0.0f, 0.0f, 0.0f };
	glm::vec3 upVec = { 0.0f, 1.0f, 0.0f };

	//  ��Դλ�á���ɫ���������壩����λ����Ϣ
	glm::vec3 lightPos = { -1.0f, 1.0f, -1.0f };
	glm::vec3 lightColor = { 1.0f, 1.0f, 1.0f };
	//  float lightVertices[36][3] = { 0 };

	//  ���塢ƽ�����ɫ������λ����Ϣ
	glm::vec3 objColor = { 0.1f, 0.1f, 0.5f };
	float objVertices[36][6] = { 0 };
	float planeVertices[36][6] = { 0 };

	//  ������ɫ
	float clearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	/*-------------------------��ʼ��---------------------*/

	//  ��ʼ���������
	setObjVertices(objVertices);
	setPlaneVertices(planeVertices);

}