#ifndef MYGUI_H

#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>

class myGUI {
public:
	myGUI() {}
	~myGUI() {}
	void createOptions() {
		ImGui::RadioButton("Orthographic-Projection", &funcSelected, 0);
		ImGui::SliderFloat("left", &orthPos[0], -4.0f, 4.0f);
		ImGui::SliderFloat("right", &orthPos[1], -4.0f, 4.0f);
		ImGui::SliderFloat("bottom", &orthPos[2], -4.0f, 4.0f);
		ImGui::SliderFloat("top", &orthPos[3], -4.0f, 4.0f);
		ImGui::SliderFloat("near-orth", &orthDist[0], 0.01f, 5.0f);
		ImGui::SliderFloat("far-orth", &orthDist[1], 1.0f, 10.0f);

		ImGui::RadioButton("Perspective-Projection", &funcSelected, 1);
		ImGui::SliderFloat("fov", &perFov, 0.0f, 180.0f);
		ImGui::SliderFloat("srceen-ratio", &srcRatio, 0.1f, 10.0f);
		ImGui::SliderFloat("near", &perDist[0], 0.01f, 3.0f);
		ImGui::SliderFloat("far", &perDist[1], 1.0f, 10.0f);


		ImGui::RadioButton("View-Changing", &funcSelected, 2);
		ImGui::SliderFloat("height", &viewHeight, 0.5f, 5.0f);
		ImGui::SliderFloat("radio", &viewRadio, 0.5f, 5.0f);

	}
	void render() {
		ImGui::Render();
	}


	int funcSelected = 0;
	//  orthPos 正交投影的范围[left, right, bottom, top]
	float orthPos[4] = { -2.0f, 2.0f, 2.0f, -2.0f };
	//  orthDist 正交投影的近、远平面[near, far]
	float orthDist[2] = { 0.01f, 50.0f };
	//  perFov 透视投影的视野 field of view
	float perFov = 45.0f;
	//  srcRatio 透视投影的视口的宽高比
	float srcRatio = 1.0f;
	//  perDist 透视投影的近、远平面[near, far]
	float perDist[2] = { 0.1f, 50.0f };
	//  viewHeight 观察视角的高度
	float viewHeight = 3.0f;
	//  viewRadio 观察视角的半径
	float viewRadio = 3.0f;
};

#endif // !MYGUI_H
