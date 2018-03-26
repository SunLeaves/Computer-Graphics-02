#ifndef MYGUI_H
#define MYGUI_H

#include <glad\glad.h>
#include <glfw\glfw3.h>
#include <imgui\imgui.h>

using namespace std;

class myGUI {
public:
	myGUI() {}
	~myGUI() {}
	void createOptions() {
		ImGui::RadioButton("Triangle", &radioChecked, 0);
		ImGui::SliderInt("vertex1.X", &vertices[0][0], -900, 900);
		ImGui::SliderInt("vertex1.Y", &vertices[0][1], -900, 900);

		ImGui::SliderInt("vertex2.X", &vertices[1][0], -900, 900);
		ImGui::SliderInt("vertex2.Y", &vertices[1][1], -900, 900);

		ImGui::SliderInt("vertex3.X", &vertices[2][0], -900, 900);
		ImGui::SliderInt("vertex3.Y", &vertices[2][1], -900, 900);
		
		ImGui::RadioButton("Circle", &radioChecked, 1);
		ImGui::SliderInt("center.X", &center[0], -300, 300);
		ImGui::SliderInt("Center.Y", &center[1], -300, 300);
		ImGui::SliderInt("radius", &radius, 10, 500);

	}
	void getCenter(int(&_center)[2]) {
		_center[0] = center[0];
		_center[1] = center[1];
	}

	void getRadius(int& _radius) {
		_radius = radius;
	}
	int getRadiochecked() {
		return radioChecked;
	}
	void getTriVertices(int (&triVertices)[3][2]) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				triVertices[i][j] = vertices[i][j];
			}
		}
	}
private:
	int radioChecked = 0;
	int radius = 100;
	int vertices[3][2] = {
		{300, 300},
		{100, 500},
		{400, 700}
	};
	int center[2] = { 100, 100 };
};

#endif